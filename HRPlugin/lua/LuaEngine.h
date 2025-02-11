#pragma once
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include "sol/sol.hpp"
#include "LuaUtils.h"
#include "LuaAPI.h"

#define RESOURCE_PATH "\\HR3"
#define SCRIPT_PATH "\\HR3\\scripts"

struct LuaScript{
	bool bLoaded = false;
	std::string szName;
	std::filesystem::path szPath;
	sol::environment* pEnvironment = nullptr;
};


class LuaEngine
{
public:
	static std::shared_ptr<LuaEngine>& Get()
	{
		static std::shared_ptr<LuaEngine> pLua = std::make_shared<LuaEngine>();
		return pLua;
	}

	void Setup()
	{
		m_crtPath = std::filesystem::current_path().string();

		std::filesystem::create_directory(m_crtPath + RESOURCE_PATH);
		std::filesystem::create_directory(m_crtPath + SCRIPT_PATH);

		g_LuaState = sol::state(sol::c_call<decltype(&LuaUtils::LuaErrorHandler), &LuaUtils::LuaErrorHandler>);
		g_LuaState.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::debug, sol::lib::package, sol::lib::jit, sol::lib::ffi, sol::lib::bit32);

		g_LuaState["print"] = LuaAPI::Print;

		g_LuaState.create_named_table(
			"HWBP_TYPE",
			"ACCESS", Script::Debug::HardwareAccess,
			"WRITE", Script::Debug::HardwareWrite,
			"EXECUTE", Script::Debug::HardwareExecute
		);

		g_LuaState.create_named_table(
			"debug",
			"run", LuaAPI::Debug::Run,
			"pause", LuaAPI::Debug::Pause,
			"stop", LuaAPI::Debug::Stop,
			"wait", LuaAPI::Debug::Wait,
			"step_in", LuaAPI::Debug::StepIn,
			"step_over", LuaAPI::Debug::StepOver,
			"step_out", LuaAPI::Debug::StepOut,
			"set_breakpoint", LuaAPI::Debug::SetBreakpoint,
			"delete_breakpoint", LuaAPI::Debug::DeleteBreakpoint,
			"disable_breakpoint", LuaAPI::Debug::DisableBreakpoint,
			"set_hardware_breakpoint", LuaAPI::Debug::SetHardwareBreakpoint,
			"delete_hardware_breakpoint", LuaAPI::Debug::DeleteHardwareBreakpoint
		);

		g_LuaState.create_named_table(
			"WINDOW_TYPE",
			"DISASSEMBLY", Script::Gui::DisassemblyWindow,
			"DUMP", Script::Gui::DumpWindow,
			"STACK", Script::Gui::StackWindow,
			"GRAPH", Script::Gui::GraphWindow,
			"MEMMAP", Script::Gui::MemMapWindow,
			"SYMMOD", Script::Gui::SymModWindow
		);

		g_LuaState.create_named_table(
			"gui",
			"get_selection_start", LuaAPI::Gui::GetSelectionStart,
			"get_selection_end", LuaAPI::Gui::GetSelectionEnd,
			"set_selection", LuaAPI::Gui::SetSelection,
			"input_line", LuaAPI::Gui::InputLine,
			"input_value", LuaAPI::Gui::InputValue,
			"message", LuaAPI::Gui::Message,
			"message_yesno", LuaAPI::Gui::MessageYesNo
		);

		g_LuaState.create_named_table(
			"memory",
			"get_base", LuaAPI::Memory::GetBase,
			"get_size", LuaAPI::Memory::GetSize,
			"get_protect", LuaAPI::Memory::GetProtect,
			"set_protect", LuaAPI::Memory::SetProtect,
			"is_valid_ptr", LuaAPI::Memory::IsValidPtr,
			"read_byte", LuaAPI::Memory::ReadByte,
			"read_word", LuaAPI::Memory::ReadWord,
			"read_dword", LuaAPI::Memory::ReadDword,
			"read_qword", LuaAPI::Memory::ReadQword,
			"read_ptr", LuaAPI::Memory::ReadPtr,
			"write_byte", LuaAPI::Memory::WriteByte,
			"write_word", LuaAPI::Memory::WriteWord,
			"write_dword", LuaAPI::Memory::WriteDword,
			"write_qword", LuaAPI::Memory::WriteQword,
			"write_ptr", LuaAPI::Memory::WritePtr,
			"remote_alloc", LuaAPI::Memory::RemoteAlloc,
			"remote_free", LuaAPI::Memory::RemoteFree
		);

		g_LuaState.create_named_table(
			"misc",
			"remote_get_proc_address", LuaAPI::Misc::RemoteGetProcAddress
		);

		g_LuaState.create_named_table(
			"module",
			"base_from_addr", LuaAPI::Module::BaseFromAddr,
			"base_from_name", LuaAPI::Module::BaseFromName,
			"entry_from_addr", LuaAPI::Module::EntryFromAddr,
			"entry_from_name", LuaAPI::Module::EntryFromName,
			"info_from_addr", LuaAPI::Module::InfoFromAddr,
			"info_from_name", LuaAPI::Module::InfoFromName,
			"get_count_of_modules", LuaAPI::Module::GetCountOfModules,
			"get_module_info_by_index", LuaAPI::Module::GetModuleInfoByIndex,
			"get_main_module_base", LuaAPI::Module::GetMainModuleBase,
			"get_main_module_size", LuaAPI::Module::GetMainModuleSize,
			"get_main_module_entry", LuaAPI::Module::GetMainModuleEntry,
			"get_main_module_info", LuaAPI::Module::GetMainModuleInfo,
			"get_main_module_name", LuaAPI::Module::GetMainModuleName,
			"get_main_module_path", LuaAPI::Module::GetMainModulePath,
			"get_main_module_section_count", LuaAPI::Module::GetMainModuleSectionCount,
			"get_main_module_section_list", LuaAPI::Module::GetMainModuleSectionInfoByIndex
		);

		g_LuaState.create_named_table(
			"pattern",
			"find_mem", LuaAPI::Pattern::FindMem
		);

		g_LuaState.create_named_table(
			"REG_TYPE",
			"DR0", Script::Register::DR0,
			"DR1", Script::Register::DR1,
			"DR2", Script::Register::DR2,
			"DR3", Script::Register::DR3,
			"DR6", Script::Register::DR6,
			"DR7", Script::Register::DR7,

			"EAX", Script::Register::EAX,
			"AX", Script::Register::AX,
			"AH", Script::Register::AH,
			"AL", Script::Register::AL,
			"EBX", Script::Register::EBX,
			"BX", Script::Register::BX,
			"BH", Script::Register::BH,
			"BL", Script::Register::BL,
			"ECX", Script::Register::ECX,
			"CX", Script::Register::CX,
			"CH", Script::Register::CH,
			"CL", Script::Register::CL,
			"EDX", Script::Register::EDX,
			"DX", Script::Register::DX,
			"DH", Script::Register::DH,
			"DL", Script::Register::DL,
			"EDI", Script::Register::EDI,
			"DI", Script::Register::DI,
			"ESI", Script::Register::ESI,
			"SI", Script::Register::SI,
			"EBP", Script::Register::EBP,
			"BP", Script::Register::BP,
			"ESP", Script::Register::ESP,
			"SP", Script::Register::SP,
			"EIP", Script::Register::EIP,

#ifdef _WIN64
			"RAX", Script::Register::RAX,
			"RBX", Script::Register::RBX,
			"RCX", Script::Register::RCX,
			"RDX", Script::Register::RDX,
			"RSI", Script::Register::RSI,
			"SIL", Script::Register::SIL,
			"RDI", Script::Register::RDI,
			"DIL", Script::Register::DIL,
			"RBP", Script::Register::RBP,
			"BPL", Script::Register::BPL,
			"RSP", Script::Register::RSP,
			"SPL", Script::Register::SPL,
			"RIP", Script::Register::RIP,

			"R8", Script::Register::R8,
			"R8D", Script::Register::R8D,
			"R8W", Script::Register::R8W,
			"R8B", Script::Register::R8B,

			"R9", Script::Register::R9,
			"R9D", Script::Register::R9D,
			"R9W", Script::Register::R9W,
			"R9B", Script::Register::R9B,

			"R10", Script::Register::R10,
			"R10D", Script::Register::R10D,
			"R10W", Script::Register::R10W,
			"R10B", Script::Register::R10B,

			"R11", Script::Register::R11,
			"R11D", Script::Register::R11D,
			"R11W", Script::Register::R11W,
			"R11B", Script::Register::R11B,

			"R12", Script::Register::R12,
			"R12D", Script::Register::R12D,
			"R12W", Script::Register::R12W,
			"R12B", Script::Register::R12B,

			"R13", Script::Register::R13,
			"R13D", Script::Register::R13D,
			"R13W", Script::Register::R13W,
			"R13B", Script::Register::R13B,

			"R14", Script::Register::R14,
			"R14D", Script::Register::R14D,
			"R14W", Script::Register::R14W,
			"R14B", Script::Register::R14B,

			"R15", Script::Register::R15,
			"R15D", Script::Register::R15D,
			"R15W", Script::Register::R15W,
			"R15B", Script::Register::R15B,

			"CIP", Script::Register::CIP,
			"CSP", Script::Register::CSP,
			"CAX", Script::Register::CAX,
			"CBX", Script::Register::CBX,
			"CCX", Script::Register::CCX,
			"CDX", Script::Register::CDX,
			"CDI", Script::Register::CDI,
			"CSI", Script::Register::CSI,
			"CBP", Script::Register::CBP,
			"CFLAGS", Script::Register::CFLAGS
#endif

		);

		g_LuaState.create_named_table(
			"register",
			"read_reg", LuaAPI::Register::ReadReg,
			"write_reg", LuaAPI::Register::WriteReg
		);



		g_LuaState.new_usertype<ModuleInfo_t>(
			"module_info_t", sol::constructors<ModuleInfo_t(), ModuleInfo_t(duint, duint, duint, int, std::string, std::string)>(),
			"base", &ModuleInfo_t::base,
			"size", &ModuleInfo_t::size,
			"entry", &ModuleInfo_t::entry,
			"section_count", &ModuleInfo_t::section_count,
			"name", &ModuleInfo_t::name,
			"path", &ModuleInfo_t::path
		);

		g_LuaState.new_usertype<ModuleSectionInfo_t>(
			"module_section_info_t", sol::constructors<ModuleSectionInfo_t()>(),
			"addr", &ModuleSectionInfo_t::addr,
			"size", &ModuleSectionInfo_t::size,
			"name", &ModuleSectionInfo_t::name
		);

		RefreshScripts();
		
	}

	void UnloadAll() {
		for (int nIndex = 0; nIndex < m_vecScripts.size(); nIndex++) {
			LuaScript* script = &m_vecScripts[nIndex];
			if (script->bLoaded) {
				UnloadScript(nIndex);
			}
		}
	}

	std::string GetScriptPath(const int nScriptID) {
		if (nScriptID == -1) {
			return "";
		}

		return m_vecScripts[nScriptID].szPath.string();
	}

	void UnloadScript(std::string szName) {
		return UnloadScript(GetScriptID(szName));
	}

	void UnloadScript(const int nScriptID) {
		if (nScriptID == -1) {
			return;
		}

		LuaScript& script = m_vecScripts[nScriptID];
		if (!script.bLoaded) {
			return;
		}

		
		script.bLoaded = false;
		delete script.pEnvironment;
		script.pEnvironment = nullptr;
	}

	void LoadScript(std::string szName) 
	{
		return LoadScript(GetScriptID(szName));
	}

	bool ScriptIsLoaded(std::string szName) 
	{
		return ScriptIsLoaded(GetScriptID(szName));
	}

	bool ScriptIsLoaded(const int nScriptID) {
		if (nScriptID == -1) {
			return false;
		}

		LuaScript& Script = m_vecScripts[nScriptID];
		return Script.bLoaded;
	}


	void LoadScript(const int nScriptID) {
		if (nScriptID == -1) {
			return;
		}

		if (m_vecScripts[nScriptID].bLoaded) {
			return;
		}

		const std::string szPath = GetScriptPath(nScriptID);
		if (szPath == "") {
			return;
		}

		LuaScript& Script = m_vecScripts[nScriptID];

		Script.bLoaded = true;
		Script.pEnvironment = new sol::environment(g_LuaState, sol::create, g_LuaState.globals());

		bool bErrorLoad = false;
		sol::environment& Environment = *Script.pEnvironment;
		auto LoadResultFunc = [&bErrorLoad, Script](lua_State* state, sol::protected_function_result Result) {
			if (!Result.valid()) {
				sol::error error = Result;
				_plugin_logputs(error.what());
				bErrorLoad = true;
			}

			return Result;
			};

		g_LuaState.safe_script_file(szPath, Environment, LoadResultFunc);
		if (bErrorLoad) {
			UnloadScript(nScriptID);
			return;
		}
	}

	void ReloadAll() 
	{

		for (int nIndex = 0; nIndex < m_vecScripts.size(); nIndex++) {
			LuaScript* script = &m_vecScripts[nIndex];
			if (script->bLoaded) {
				UnloadScript(nIndex);
				LoadScript(nIndex);
			}
		}
	}

	int GetScriptID(std::string szName) {
		for (int nIndex = 0; nIndex < m_vecScripts.size(); nIndex++) {
			if (m_vecScripts.at(nIndex).szName == szName) {
				return nIndex;
			}
		}

		return -1;
	}

	void RefreshScripts()
	{
		std::vector<LuaScript> vecOldScripts = m_vecScripts;

		UnloadAll();
		m_vecScripts.clear();
		for (auto& Entry : std::filesystem::directory_iterator(m_crtPath + SCRIPT_PATH)) {
			if (Entry.path().extension() == ".lua") {
				LuaScript Script;
				Script.bLoaded = false;
				bool bWasLoaded = false;
				Script.szPath = Entry.path();
				Script.szName = Script.szPath.stem().string();
				for (auto& OldScript : m_vecScripts) {
					if (OldScript.szName == Script.szName && OldScript.bLoaded) {
						bWasLoaded = true;
						break;
					}
				}

				m_vecScripts.push_back(Script);
			}
		}

		for (auto& Script : vecOldScripts) {
			if (Script.bLoaded) {
				LoadScript(GetScriptID(Script.szName));
			}
		}
	}

private:
	std::vector<LuaScript> m_vecScripts;
	std::string m_crtPath;
};