#include "lua_args.h"

LuaArgs::LuaArgs(lua_State* _L)
{
	L = _L;
	index = 0;
    pushed = 0;

    //lua_checkstack();   
}

int LuaArgs::getInt()
{
	index++;
	return luaL_checkint(L, index);
}

float LuaArgs::getFloat()
{
	index++;
	return (float)luaL_checknumber(L, index);
}

const char* LuaArgs::getString()
{
    index++;
    return luaL_checkstring(L, index);
}

BOOL LuaArgs::getBool()
{
	index++;
	luaL_checktype(L, index, LUA_TBOOLEAN);

	return lua_toboolean(L, index);
}

Vector3 LuaArgs::getVector3()
{
    index++;
    luaL_checktype(L, index, LUA_TTABLE);

    lua_pushstring(L, "x");
    lua_rawget(L, index);
    auto x = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "y");
    lua_rawget(L, index);
    auto y = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "z");
    lua_rawget(L, index);
    auto z = lua_tonumber(L, -1);
    lua_pop(L, 1);

    return {
        .x = (float)x,
        .y = (float)y,
        .z = (float)z,
    };
}

DWORD LuaArgs::getDword()
{
    index++;
    return (DWORD)luaL_checkinteger(L, index);
}

Any* LuaArgs::getAnyPtr()
{
    index++;
    luaL_checktype(L, index, 10); // LuaJIT cdata type
    return (Any*)lua_topointer(L, index);
}

void LuaArgs::pushInt(int i)
{
    lua_pushinteger(L, i);
    pushed++;
}

void LuaArgs::pushFloat(float f)
{
    lua_pushnumber(L, f);
    pushed++;
}

void LuaArgs::pushString(const char* s)
{
    lua_pushstring(L, s);
    pushed++;
}

void LuaArgs::pushBool(BOOL b)
{
    lua_pushboolean(L, b);
    pushed++;
}

void LuaArgs::pushVector3(Vector3 v, int index)
{
    if (index == NULL)
    {
        lua_newtable(L);
        index = -3;
        pushed++;
    }

    lua_pushstring(L, "x");
    lua_pushnumber(L, v.x);
    lua_rawset(L, index);

    lua_pushstring(L, "y");
    lua_pushnumber(L, v.y);
    lua_rawset(L, index);

    lua_pushstring(L, "z");
    lua_pushnumber(L, v.z);
    lua_rawset(L, index);
}

void LuaArgs::pushDword(DWORD d)
{
    lua_pushinteger(L, d);
    pushed++;
}