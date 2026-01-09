#include "lua.h"

using namespace std;
namespace fs = std::filesystem;

lua_State* L;

Thread* currentThread;
vector<Thread> threads;

const char* getLuaErrorDescription(int error)
{
    switch (error)
    {
    case LUA_ERRRUN:
        return "Runtime error";
    case LUA_ERRSYNTAX:
        return "Syntax error";
    case LUA_ERRMEM:
        return "Memory allocation error";
    case LUA_ERRERR:
        return "Error in the error handler function";
    case LUA_ERRFILE:
        return "Failed to load file";
    }

    return "Unknown error";
}

void luaInitialize()
{
    L = luaL_newstate();

    if (!L)
    {
        return;
    }

    std::cout << "[PLUGIN] Lua state initialized." << std::endl;

    luaL_openlibs(L);
    luaRegisterNatives(L);
    luaRegisterFunctions(L);

    std::cout << "[PLUGIN] Registered Lua libraries, functions and natives." << std::endl;
}

void luaSearchForScripts()
{
    if (!L)
    {
        return;
    }

    if (!fs::exists("lua") || !fs::is_directory("lua"))
    {
        std::cout << "No \"lua\" folder found in the game root directory." << std::endl;
        return;
    }

    std::cout << std::endl << "[PLUGIN] Searching for Lua scripts..." << std::endl;

    for (const fs::directory_entry& entry : fs::directory_iterator("lua"))
    {
        fs::path path = entry.path();

        if (!fs::is_regular_file(entry) || path.extension() != ".lua")
        {
            continue;
        }

        std::cout << std::endl << "[PLUGIN] Found file \"" << path.string() << "\"." << std::endl;

        Thread thread(path);

        if (thread.thread)
        {
            threads.push_back(thread);
        }
    }

    std::cout << std::endl << "[PLUGIN] Finished searching for Lua scripts. Created " << threads.size() << " permanent threads." << std::endl << std::endl;
}

void luaTick()
{
    for (Thread& thread : threads)
    {
        thread.tick();
    }
}
 
void luaTerminate()
{
    std::cout << "[PLUGIN] Terminating Lua threads..." << std::endl;

    for (Thread& thread : threads)
    {
        thread.unload();
    }

    threads.clear();

    std::cout << "[PLUGIN] Lua threads terminated." << std::endl;

    if (L)
    {
        lua_close(L);
        L = nullptr;
    }
    
    std::cout << "[PLUGIN] Lua state terminated." << std::endl;
}

Thread::Thread(fs::path path)
{
    this->name = path.filename().string();
    this->thread = lua_newthread(L);
    this->unloadHandlerRef = LUA_NOREF;

    auto error = luaL_loadfile(this->thread, path.string().c_str());

    if (error)
    {
        std::cout << "[PLUGIN] [ERROR - " << getLuaErrorDescription(error) << " (" << error << ")] while loading script: " << lua_tostring(this->thread, -1) << std::endl;
        this->thread = nullptr;
        return;
    }

    std::cout << "[PLUGIN] Script created sucessfully." << std::endl;

    this->tick();
}

void Thread::tick()
{
    if (!this->thread)
    {
        return;
    }

    currentThread = this;

    auto status = lua_resume(this->thread, 0);

    if (status == LUA_YIELD)
    {
        currentThread = nullptr;
        return;
    }

    if (status != LUA_OK && lua_isstring(this->thread, -1))
    {
        std::cout << "[PLUGIN] [ERROR " << status << " - " << getLuaErrorDescription(status) << "]: " << lua_tostring(this->thread, -1) << std::endl;
        lua_pop(this->thread, 1);
    }
    else
    {
        std::cout << "[PLUGIN] Lua script " << this->name << " finished sucessfully." << std::endl;
    }

    unload();

    lua_settop(this->thread, 0);
    this->thread = nullptr;
}

void Thread::unload()
{
    if (!this->thread)
    {
        return;
    }

    currentThread = this;

    if (this->unloadHandlerRef != LUA_NOREF)
    {
        lua_rawgeti(this->thread, LUA_REGISTRYINDEX, this->unloadHandlerRef);

        if (lua_isfunction(this->thread, -1))
        {
            auto error = lua_pcall(this->thread, 0, 0, 0);

            if (error)
            {
                std::cout << "[PLUGIN] [ERROR " << error << " - " << getLuaErrorDescription(error) << "]: " << lua_tostring(this->thread, -1) << std::endl;
            }
        }

        luaL_unref(this->thread, LUA_REGISTRYINDEX, this->unloadHandlerRef);
    }

    currentThread = nullptr;
}

Thread* getCurrentThread()
{
    return currentThread;
}