#ifndef NATIVES_H
#define NATIVES_H

#include "../luajit/lua.hpp"
#include "../shv/natives.h"
#include "lua_args.h"

#define lua_registertablefield(L, name, function) (lua_pushstring(L, name), lua_pushcfunction(L, function), lua_rawset(L, -3))

void luaRegisterNatives(lua_State* L);
#endif // !NATIVES_H