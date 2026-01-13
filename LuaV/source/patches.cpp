#include "patches.h"

static int lua_DRAW_MARKER(lua_State* L)
{
	LuaArgs largs(L);

	auto type = largs.getInt();
	auto posX = largs.getFloat();
	auto posY = largs.getFloat();
	auto posZ = largs.getFloat();
	auto dirX = largs.getFloat();
	auto dirY = largs.getFloat();
	auto dirZ = largs.getFloat();
	auto rotX = largs.getFloat();
	auto rotY = largs.getFloat();
	auto rotZ = largs.getFloat();
	auto scaleX = largs.getFloat();
	auto scaleY = largs.getFloat();
	auto scaleZ = largs.getFloat();
	auto red = largs.getInt();
	auto green = largs.getInt();
	auto blue = largs.getInt();
	auto alpha = largs.getInt();
	auto bobUpAndDown = largs.getBool();
	auto faceCamera = largs.getBool();
	auto p19 = largs.getInt();
	auto rotate = largs.getBool();
	auto textureDict = largs.getString();
	auto textureName = largs.getString();
	auto drawOnEnts = largs.getBool();
	GRAPHICS::DRAW_MARKER(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, nullptr, nullptr, drawOnEnts);

	return largs.pushed;
}

static int lua_DRAW_MARKER_EX(lua_State* L)
{
	LuaArgs largs(L);

	auto type = largs.getInt();
	auto posX = largs.getFloat();
	auto posY = largs.getFloat();
	auto posZ = largs.getFloat();
	auto dirX = largs.getFloat();
	auto dirY = largs.getFloat();
	auto dirZ = largs.getFloat();
	auto rotX = largs.getFloat();
	auto rotY = largs.getFloat();
	auto rotZ = largs.getFloat();
	auto scaleX = largs.getFloat();
	auto scaleY = largs.getFloat();
	auto scaleZ = largs.getFloat();
	auto red = largs.getInt();
	auto green = largs.getInt();
	auto blue = largs.getInt();
	auto alpha = largs.getInt();
	auto bobUpAndDown = largs.getBool();
	auto faceCamera = largs.getBool();
	auto p19 = largs.getDword();
	auto rotate = largs.getBool();
	auto textureDict = largs.getString();
	auto textureName = largs.getString();
	auto drawOnEnts = largs.getBool();
	auto p24 = largs.getBool();
	auto p25 = largs.getBool();
	GRAPHICS::DRAW_MARKER_EX(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, nullptr, nullptr, drawOnEnts, p24, p25);

	return largs.pushed;
}

void luaApplyPatches(lua_State* L)
{
	lua_getglobal(L, "GRAPHICS");

	if (lua_istable(L, -1))
	{
		lua_registertablefield(L, "DRAW_MARKER", lua_DRAW_MARKER);
		lua_registertablefield(L, "DRAW_MARKER_EX", lua_DRAW_MARKER_EX);
	}
}