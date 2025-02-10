#pragma once
#include <iostream>
#include "sol/sol.hpp"

extern sol::state g_LuaState;

namespace LuaUtils
{

	struct LuaCheckArgumentType 
	{
		sol::type typeSrc;
		sol::type typeTarget;
	};

	std::time_t GetTimeStamp();

	std::string GetCurrentScript(sol::this_state State);

	std::string GetArgumentType(sol::type type);

	bool CheckArgument(std::vector<LuaCheckArgumentType> vecArguments);

	void LuaErrorHandler(sol::this_state State, sol::optional<std::string> szMessage);

}
