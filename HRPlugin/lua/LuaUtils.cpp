#include "LuaUtils.h"
#include <filesystem>
#include <chrono>
#include "pluginmain.h"

sol::state g_LuaState;

std::time_t LuaUtils::GetTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> TimePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	return TimePoint.time_since_epoch().count();
}

std::string LuaUtils::GetCurrentScript(sol::this_state State)
{
	sol::state_view lua_state(State);
	sol::table rs = lua_state["debug"]["getinfo"](2, "S");
	std::string source = rs["source"];
	std::string filename = std::filesystem::path(source.substr(1)).stem().string();
	return filename;
}

std::string LuaUtils::GetArgumentType(sol::type type)
{
	switch (type)
	{
	case sol::type::nil: return "nil";
	case sol::type::table: return "table";
	case sol::type::string: return "string";
	case sol::type::number: return "number";
	case sol::type::thread: return "thread";
	case sol::type::boolean: return "boolean";
	case sol::type::function: return "function";
	case sol::type::userdata: return "userdata";
	case sol::type::lightuserdata: return "lightuserdata";
	}

	return "?";
}

bool LuaUtils::CheckArgument(std::vector<LuaCheckArgumentType> vecArguments)
{
	for (int nIndex = 0; nIndex < vecArguments.size(); nIndex++)
	{
		if (vecArguments.at(nIndex).typeSrc != vecArguments.at(nIndex).typeTarget)
		{
			char buffer[512]{ 0 };
			sprintf_s(buffer, sizeof(buffer), "lua error: invalid argument #%d, need: %s, gived: %s", nIndex + 1, GetArgumentType(vecArguments.at(nIndex).typeTarget).c_str(), GetArgumentType(vecArguments.at(nIndex).typeSrc).c_str());
			_plugin_logputs(buffer);
			return false;
		}
	}

	return true;
}

void LuaUtils::LuaErrorHandler(sol::this_state State, sol::optional<std::string> szMessage)
{
	if (!szMessage.has_value())
	{
		return;
	}

	std::string szError = szMessage.value();
	std::string szScriptName = GetCurrentScript(State);
	const std::time_t nCurrentTimestamp = GetTimeStamp();
	std::size_t nScriptNamePosition = szError.find(szScriptName);
	if (nScriptNamePosition != std::string::npos)
	{
		szError = szError.substr(nScriptNamePosition, szError.size());
	}

	char buffer[512]{ 0 };
	sprintf_s(buffer, sizeof(buffer), "lua error: %s", szError.c_str());
	_plugin_logputs(buffer);

}