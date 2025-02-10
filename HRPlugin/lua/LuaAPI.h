#pragma once
#include <iostream>
#include "LuaUtils.h"
#include "sol/sol.hpp"
#include "pluginmain.h"

struct ModuleInfo_t
{
	duint base;
	duint size;
	duint entry;
	int section_count;
	std::string name;
	std::string path;

	ModuleInfo_t()
	{
		base = 0;
		size = 0;
		entry = 0;
		section_count = 0;
		name.clear();
		path.clear();
	}

	ModuleInfo_t(duint uBase, duint uSize, duint uEntry, int nSectionCount, std::string szName, std::string szPath) :
		base(uBase), size(uSize), entry(uEntry), section_count(nSectionCount), name(szName), path(szPath)
	{

	}
};

struct ModuleSectionInfo_t
{
	duint addr;
	duint size;
	std::string name;

	ModuleSectionInfo_t()
	{
		addr = 0;
		size = 0;
		name.clear();
	}

	ModuleSectionInfo_t(duint uAddr, duint uSize, std::string szName)
	{
		addr = uAddr;
		size = uSize;
		name = szName;
	}

};

namespace LuaAPI
{
	void Print(sol::this_state State, sol::object objMessage);

	namespace Debug
	{
		void Run(sol::this_state state);

		void Pause(sol::this_state state);

		void Stop(sol::this_state state);

		void Wait(sol::this_state state);

		void StepIn(sol::this_state state);

		void StepOver(sol::this_state state);

		void StepOut(sol::this_state state);

		void SetBreakpoint(sol::this_state state, duint uAddress);

		void DeleteBreakpoint(sol::this_state state, duint uAddress);

		void DisableBreakpoint(sol::this_state state, duint uAddress);

		void SetHardwareBreakpoint(sol::this_state state, duint uAddress, int nType);

		void DeleteHardwareBreakpoint(sol::this_state state, duint uAddress);

	}

	namespace Gui
	{
		
		duint GetSelectionStart(sol::this_state state, int nType);

		duint GetSelectionEnd(sol::this_state state, int nType);
		
		bool SetSelection(sol::this_state state, int nType, duint uStart, duint uEnd);

		std::string InputLine(sol::this_state state, const char* szTitle);

		duint InputValue(sol::this_state state, const char* szTitle);

		void Message(sol::this_state state, const char* szMsg);

		bool MessageYesNo(sol::this_state state, const char* szMsg);

	}

	namespace Memory
	{

		duint GetBase(sol::this_state state, duint uAddress);

		duint GetSize(sol::this_state state, duint uAddress);

		uint32_t GetProtect(sol::this_state state, duint uAddress);

		bool SetProtect(sol::this_state state, duint uAddress, uint32_t uProtect, duint size);

		bool IsValidPtr(sol::this_state state, duint uAddress);

		uint8_t ReadByte(sol::this_state state, duint uAddress);

		uint16_t ReadWord(sol::this_state state, duint uAddress);

		uint32_t ReadDword(sol::this_state state, duint uAddress);

		uint64_t ReadQword(sol::this_state state, duint uAddress);

		duint ReadPtr(sol::this_state state, duint uAddress);

		bool WriteByte(sol::this_state state, duint uAddress, uint8_t data);

		bool WriteWord(sol::this_state state, duint uAddress, uint16_t data);

		bool WriteDword(sol::this_state state, duint uAddress, uint32_t data);

		bool WriteQword(sol::this_state state, duint uAddress, void* data);

		bool WritePtr(sol::this_state state, duint uAddress, duint data);

		duint RemoteAlloc(sol::this_state state, duint uAddress, duint size);

		bool RemoteFree(sol::this_state state, duint uAddress);

	}

	namespace Misc
	{
		duint RemoteGetProcAddress(sol::this_state state, const char* szModule, const char* szFunc);
	}

	namespace Module
	{

		duint BaseFromAddr(sol::this_state state, duint uAddress);

		duint BaseFromName(sol::this_state state, const char* szName);

		duint EntryFromAddr(sol::this_state state, duint uAddress);

		duint EntryFromName(sol::this_state state, const char* szName);

		ModuleInfo_t InfoFromAddr(sol::this_state state, duint uAddress);

		ModuleInfo_t InfoFromName(sol::this_state state, const char* szName);

		sol::table GetList(sol::this_state state);

		duint GetMainModuleBase(sol::this_state state);

		duint GetMainModuleSize(sol::this_state state);

		duint GetMainModuleEntry(sol::this_state state);

		sol::object GetMainModuleInfo(sol::this_state state);

		std::string GetMainModuleName(sol::this_state state);

		std::string GetMainModulePath(sol::this_state state);

		int GetMainModuleSectionCount(sol::this_state state);

		sol::table GetMainModuleSectionList(sol::this_state state);

	}

	namespace Pattern
	{
		duint FindMem(sol::this_state state, duint uStart, duint size, const char* pattern);
	}

	namespace Register
	{
		duint ReadReg(int nType);

		bool WriteReg(int nType, duint value);

	}

}