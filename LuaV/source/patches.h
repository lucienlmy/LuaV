#ifndef PATCHES_H
#define PATCHES_H

#include "../luajit/lua.hpp"
#include "../shv/natives.h"
#include "lua_args.h"

void luaApplyPatches(lua_State* L);

#endif // !PATCHES_H