#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../luajit/lua.hpp"
#include "lua_args.h"
#include "lua.h"
#include "keyboard.h"

const auto WORLD_GET_ALL_ARRAY_SIZE = 1024;
const auto PLUGIN_VERSION = 100; // x.x.x // MAJOR.MINOR.PATCH

void luaRegisterFunctions(lua_State* L);
#endif // !KEYBOARD_H