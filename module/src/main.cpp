#include <iostream>
#include <mhttp.hpp>
#include <GarrysMod/Lua/Interface.h>

#include "util.hpp";

using namespace GarrysMod::Lua;

LUA_FUNCTION(mhttp_impl)
{
	LUA->CheckType(1, Type::String);

	LUA->PushSpecial(SPECIAL_GLOB);
		LUA->GetField(-1, "print");
		LUA->Push(1);
		LUA->Call(1, 0);
	LUA->Pop();

	return 0;
}

GMOD_MODULE_OPEN()
{
	gmsv_mhttp::Log(LUA, "Hello, world!");

	// Push the "mhttp" function onto the global stack.
	LUA->PushSpecial(SPECIAL_GLOB);
		LUA->PushCFunction(mhttp_impl);
		LUA->SetField(-2, "mhttp");
	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}