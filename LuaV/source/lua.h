#ifndef LUA_H
#define LUA_H

#include <iostream>
#include <filesystem>
#include "../luajit/lua.hpp"
#include "../shv/types.h"
#include "natives.h"
#include "patches.h"
#include "functions.h"

struct Thread
{
    std::string name;
    lua_State* thread;
    int unloadHandlerRef;

    Thread(std::filesystem::path path);

    void tick();
    void unload();
};

Thread* getCurrentThread();

void luaInitialize();
void luaSearchForScripts();
void luaTick();
void luaTerminate();
#endif // !LUA_H