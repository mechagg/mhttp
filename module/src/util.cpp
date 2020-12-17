#include "util.hpp"

namespace gmsv_mhttp
{
	// CreateColor returns a reference to a lua table that is a valid color.
	int CreateColor(GarrysMod::Lua::ILuaBase *L, double r, double g, double b)
	{
		L->CreateTable();

		L->PushNumber(r);
		L->SetField(-2, "r");

		L->PushNumber(g);
		L->SetField(-2, "g");

		L->PushNumber(b);
		L->SetField(-2, "b");
		
		return L->ReferenceCreate();
	}

	// Log prints a message to the console with an "mhttp" tag.
	void Log(GarrysMod::Lua::ILuaBase *L, char* message)
	{
		auto tagColor = CreateColor(L, 255, 0, 0);
		auto messageColor = CreateColor(L, 255, 255, 255);

		L->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			L->GetField(-1, "MsgC");

			L->ReferencePush(tagColor);
			L->PushString("mhttp | ");

			L->ReferencePush(messageColor);
			L->PushString(message);

			L->PushString("\n");

			L->Call(5, 0);
		L->Pop();

		L->ReferenceFree(tagColor);
		L->ReferenceFree(messageColor);
	}
}