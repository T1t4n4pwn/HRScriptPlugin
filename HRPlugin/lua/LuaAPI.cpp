#include "LuaAPI.h"

void LuaAPI::Print(sol::this_state State, sol::object objMessage)
{
	_plugin_logputs(g_LuaState["tostring"](objMessage).get<std::string>().c_str());
}

void LuaAPI::Debug::Run(sol::this_state state)
{
	Script::Debug::Run();
}

void LuaAPI::Debug::Pause(sol::this_state state)
{
	Script::Debug::Pause();
}

void LuaAPI::Debug::Stop(sol::this_state state)
{
	Script::Debug::Stop();
}

void LuaAPI::Debug::Wait(sol::this_state state)
{
	Script::Debug::Wait();
}

void LuaAPI::Debug::StepIn(sol::this_state state)
{
	Script::Debug::StepIn();
}

void LuaAPI::Debug::StepOver(sol::this_state state)
{
	Script::Debug::StepOver();
}

void LuaAPI::Debug::StepOut(sol::this_state state)
{
	Script::Debug::StepOut();
}

void LuaAPI::Debug::SetBreakpoint(sol::this_state state, duint uAddress)
{
	Script::Debug::SetBreakpoint(uAddress);
}

void LuaAPI::Debug::DeleteBreakpoint(sol::this_state state, duint uAddress)
{
	Script::Debug::DeleteBreakpoint(uAddress);
}

void LuaAPI::Debug::DisableBreakpoint(sol::this_state state, duint uAddress)
{
	Script::Debug::DisableBreakpoint(uAddress);
}

void LuaAPI::Debug::SetHardwareBreakpoint(sol::this_state state, duint uAddress, int nType)
{
	Script::Debug::SetHardwareBreakpoint(uAddress, (Script::Debug::HardwareType)nType);
}

void LuaAPI::Debug::DeleteHardwareBreakpoint(sol::this_state state, duint uAddress)
{
	Script::Debug::DeleteHardwareBreakpoint(uAddress);
}

duint LuaAPI::Gui::GetSelectionStart(sol::this_state state, int nType)
{
	return Script::Gui::SelectionGetStart((Script::Gui::Window)nType);
}

duint LuaAPI::Gui::GetSelectionEnd(sol::this_state state, int nType)
{
	return Script::Gui::SelectionGetEnd((Script::Gui::Window)nType);
}

bool LuaAPI::Gui::SetSelection(sol::this_state state, int nType, duint uStart, duint uEnd)
{
	return Script::Gui::SelectionSet((Script::Gui::Window)nType, uStart, uEnd);
}

std::string LuaAPI::Gui::InputLine(sol::this_state state, const char* szTitle)
{
	char buffer[512]{ 0 };
	Script::Gui::InputLine(szTitle, buffer);

	return std::string(buffer);
}

duint LuaAPI::Gui::InputValue(sol::this_state state, const char* szTitle)
{
	duint value = 0;
	Script::Gui::InputValue(szTitle, &value);

	return value;
}

void LuaAPI::Gui::Message(sol::this_state state, const char* szMsg)
{
	Script::Gui::Message(szMsg);
}

bool LuaAPI::Gui::MessageYesNo(sol::this_state state, const char* szMsg)
{
	return Script::Gui::MessageYesNo(szMsg);
}

duint LuaAPI::Memory::GetBase(sol::this_state state, duint uAddress)
{
	return Script::Memory::GetBase(uAddress);
}

duint LuaAPI::Memory::GetSize(sol::this_state state, duint uAddress)
{
	return Script::Memory::GetSize(uAddress);
}

uint32_t LuaAPI::Memory::GetProtect(sol::this_state state, duint uAddress)
{
	return Script::Memory::GetProtect(uAddress);
}

bool LuaAPI::Memory::SetProtect(sol::this_state state, duint uAddress, uint32_t uProtect, duint size)
{
	return Script::Memory::SetProtect(uAddress, uProtect, size);
}

bool LuaAPI::Memory::IsValidPtr(sol::this_state state, duint uAddress)
{
	return Script::Memory::IsValidPtr(uAddress);
}

uint8_t LuaAPI::Memory::ReadByte(sol::this_state state, duint uAddress)
{
	return Script::Memory::ReadByte(uAddress);
}

uint16_t LuaAPI::Memory::ReadWord(sol::this_state state, duint uAddress)
{
	return Script::Memory::ReadWord(uAddress);
}

uint32_t LuaAPI::Memory::ReadDword(sol::this_state state, duint uAddress)
{
	return Script::Memory::ReadDword(uAddress);
}

uint64_t LuaAPI::Memory::ReadQword(sol::this_state state, duint uAddress)
{
	return Script::Memory::ReadQword(uAddress);
}

duint LuaAPI::Memory::ReadPtr(sol::this_state state, duint uAddress)
{
	return Script::Memory::ReadPtr(uAddress);
}

bool LuaAPI::Memory::WriteByte(sol::this_state state, duint uAddress, uint8_t data)
{
	return Script::Memory::WriteByte(uAddress, data);
}

bool LuaAPI::Memory::WriteWord(sol::this_state state, duint uAddress, uint16_t data)
{
	return Script::Memory::WriteWord(uAddress, data);
}

bool LuaAPI::Memory::WriteDword(sol::this_state state, duint uAddress, uint32_t data)
{
	return Script::Memory::WriteDword(uAddress, data);
}

bool LuaAPI::Memory::WriteQword(sol::this_state state, duint uAddress, void* data)
{
	return Script::Memory::WriteQword(uAddress, (uint64_t)data);
}

bool LuaAPI::Memory::WritePtr(sol::this_state state, duint uAddress, duint data)
{
	return Script::Memory::WritePtr(uAddress, data);
}

duint LuaAPI::Memory::RemoteAlloc(sol::this_state state, duint uAddress, duint size)
{
	return Script::Memory::RemoteAlloc(uAddress, size);
}

bool LuaAPI::Memory::RemoteFree(sol::this_state state, duint uAddress)
{
	return Script::Memory::RemoteFree(uAddress);
}

duint LuaAPI::Misc::RemoteGetProcAddress(sol::this_state state, const char* szModule, const char* szFunc)
{
	return Script::Misc::RemoteGetProcAddress(szModule, szFunc);
}

duint LuaAPI::Module::BaseFromAddr(sol::this_state state, duint uAddress)
{
	return Script::Module::BaseFromAddr(uAddress);
}

duint LuaAPI::Module::BaseFromName(sol::this_state state, const char* szName)
{
	return Script::Module::BaseFromName(szName);
}

duint LuaAPI::Module::EntryFromAddr(sol::this_state state, duint uAddress)
{
	return Script::Module::EntryFromAddr(uAddress);
}

duint LuaAPI::Module::EntryFromName(sol::this_state state, const char* szName)
{
	return Script::Module::EntryFromName(szName);
}

ModuleInfo_t LuaAPI::Module::InfoFromAddr(sol::this_state state, duint uAddress)
{

	Script::Module::ModuleInfo moduleInfo{ 0 };
	Script::Module::InfoFromAddr(uAddress, &moduleInfo);

	ModuleInfo_t info(moduleInfo.base, moduleInfo.size, moduleInfo.entry, moduleInfo.sectionCount, moduleInfo.name, moduleInfo.path);

	return info;
}

ModuleInfo_t LuaAPI::Module::InfoFromName(sol::this_state state, const char* szName)
{

	Script::Module::ModuleInfo moduleInfo{ 0 };
	Script::Module::InfoFromName(szName, &moduleInfo);

	ModuleInfo_t info(moduleInfo.base, moduleInfo.size, moduleInfo.entry, moduleInfo.sectionCount, moduleInfo.name, moduleInfo.path);

	return info;
}

sol::table LuaAPI::Module::GetList(sol::this_state state)
{

	ListInfo info;
	if (!Script::Module::GetList(&info))
	{
		return sol::nil;
	}

	sol::table tlbInfos = g_LuaState.create_table(state);

	int nIndex = 0;
	for (int i = 0; i < info.count; i++)
	{
		Script::Module::ModuleInfo* pModInfo = (Script::Module::ModuleInfo*)info.data;
		//TODO Fix crash
		tlbInfos[++nIndex] = sol::make_object(state, ModuleInfo_t(pModInfo[i].base, pModInfo[i].size, pModInfo[i].entry, pModInfo[i].sectionCount, pModInfo[i].name, pModInfo[i].path));
	}

	return tlbInfos;
}

duint LuaAPI::Module::GetMainModuleBase(sol::this_state state)
{
	return Script::Module::GetMainModuleBase();
}

duint LuaAPI::Module::GetMainModuleSize(sol::this_state state)
{
	return Script::Module::GetMainModuleSize();
}

duint LuaAPI::Module::GetMainModuleEntry(sol::this_state state)
{
	return Script::Module::GetMainModuleEntry();
}

sol::object LuaAPI::Module::GetMainModuleInfo(sol::this_state state)
{
	Script::Module::ModuleInfo moduleInfo;
	if (!Script::Module::GetMainModuleInfo(&moduleInfo))
	{
		return sol::nil;
	}
	ModuleInfo_t info(moduleInfo.base, moduleInfo.size, moduleInfo.entry, moduleInfo.sectionCount, moduleInfo.name, moduleInfo.path);
	return sol::make_object(state, info);
}

std::string LuaAPI::Module::GetMainModuleName(sol::this_state state)
{
	char buffer[512]{ 0 };
	Script::Module::GetMainModuleName(buffer);

	return std::string(buffer);
}

std::string LuaAPI::Module::GetMainModulePath(sol::this_state state)
{
	char buffer[512]{ 0 };
	Script::Module::GetMainModulePath(buffer);

	return std::string(buffer);
}

int LuaAPI::Module::GetMainModuleSectionCount(sol::this_state state)
{
	return Script::Module::GetMainModuleSectionCount();
}

sol::table LuaAPI::Module::GetMainModuleSectionList(sol::this_state state)
{
	ListInfo info;
	if (!Script::Module::GetMainModuleSectionList(&info))
	{
		return sol::nil;
	}

	sol::table tlbInfos = g_LuaState.create_table(state);

	int nIndex = 0;
	for (int i = 0; i < info.count; i++)
	{
		Script::Module::ModuleSectionInfo* pModInfo = (Script::Module::ModuleSectionInfo*)info.data;
		//TODO Fix crash
		tlbInfos[++nIndex] = sol::make_object(state, ModuleSectionInfo_t(pModInfo[i].addr, pModInfo[i].size, pModInfo[i].name));
	}

	return tlbInfos;
}

duint LuaAPI::Pattern::FindMem(sol::this_state state, duint uStart, duint size, const char* pattern)
{
	return Script::Pattern::FindMem(uStart, size, pattern);
}

duint LuaAPI::Register::ReadReg(int nType)
{
	return Script::Register::Get((Script::Register::RegisterEnum)nType);
}

bool LuaAPI::Register::WriteReg(int nType, duint value)
{
	return Script::Register::Set((Script::Register::RegisterEnum)nType, value);
}