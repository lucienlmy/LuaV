#ifndef NATIVES_H
#define NATIVES_H

#include "../luajit/lua.hpp"
#include "../shv/natives.h"
#include "lua_args.h"

void luaRegisterNatives(lua_State* L);
#endif // !NATIVES_H