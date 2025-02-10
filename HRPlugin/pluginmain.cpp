#include <WinSock2.h>
#include "pluginmain.h"
#include "plugin.h"
#include <iostream>
#include <string>
#include <intrin.h>

#include "lua/LuaEngine.h"

int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;

enum TabEnum
{
    LOAD_SCRIPT,
    UNLOAD_SCRIPT,
};

PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    initStruct->pluginVersion = PLUGIN_VERSION;
    initStruct->sdkVersion = PLUG_SDKVERSION;
    strncpy_s(initStruct->pluginName, PLUGIN_NAME, _TRUNCATE);
    pluginHandle = initStruct->pluginHandle;

    LuaEngine::Get()->Setup();

    return pluginInit(initStruct);
}

PLUG_EXPORT bool plugstop()
{
    return pluginStop();
}

void MenuEntry(CBTYPE cbType, void* callbackInfo)
{
    PLUG_CB_MENUENTRY* info = (PLUG_CB_MENUENTRY*)callbackInfo;

    switch (info->hEntry)
    {
    case LOAD_SCRIPT:
    {
        LuaEngine::Get()->RefreshScripts();
        LuaEngine::Get()->LoadScript("test");
        break;
    }
    case UNLOAD_SCRIPT:
    {
        LuaEngine::Get()->UnloadScript("test");
        break;
    }
    default:
        break;
    }
}

PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    hwndDlg = setupStruct->hwndDlg;
    hMenu = setupStruct->hMenu;
    hMenuDisasm = setupStruct->hMenuDisasm;
    hMenuDump = setupStruct->hMenuDump;
    hMenuStack = setupStruct->hMenuStack;
    pluginSetup();
    _plugin_menuadd(hMenuDisasm, PLUGIN_NAME);
    _plugin_menuaddentry(hMenuDisasm, LOAD_SCRIPT, "LoadScript");
    _plugin_menuaddentry(hMenuDisasm, UNLOAD_SCRIPT, "UnloadScript");
    _plugin_registercallback(pluginHandle, CB_MENUENTRY, MenuEntry);
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD     fdwReason,
    _In_ LPVOID    lpvReserved
)
{
    return TRUE;
}
