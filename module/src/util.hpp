#pragma once

#include <GarrysMod/Lua/Interface.h>

namespace gmsv_mhttp
{
	// CreateColor returns a reference to a lua table that is a valid color.
	int CreateColor(GarrysMod::Lua::ILuaBase* L, double r, double g, double b);

	// Log prints a message to the console with an "mhttp" tag.
	void Log(GarrysMod::Lua::ILuaBase* L, char* message);
}