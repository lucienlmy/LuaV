#ifndef LUA_ARGS_H
#define LUA_ARGS_H

#include "../luajit/lua.hpp"
#include "../shv/types.h"

struct LuaArgs
{
	lua_State* L;
	int index;
	int pushed;

	LuaArgs(lua_State* _L);

	int getInt();
	float getFloat();
	const char* getString();
	BOOL getBool();
	Vector3 getVector3();
	DWORD getDword();
	Any* getAnyPtr();

	void pushInt(int i);
	void pushFloat(float f);
	void pushString(const char* s);
	void pushBool(BOOL b);
	void pushVector3(Vector3 v, int index = 0);
	void pushDword(DWORD d);
};
#endif // !LUA_ARGS_H