#include <llapi/LoggerAPI.h>
#include <llapi/ServerAPI.h>

#include <stdio.h>
#include <WinNls.h>

#include <windows.h>
#include <cstdio> 

#include "version.h"

void PluginInit();

Logger logger(PLUGIN_NAME);

void CheckProtocolVersion()
{

#ifdef TARGET_BDS_PROTOCOL_VERSION

    auto current_protocol = ll::getServerProtocolVersion();
    if (TARGET_BDS_PROTOCOL_VERSION != current_protocol)
    {
        logger.error("不兼容的BDS版本！本插件兼容 BDS-1.19.40 , 版本协议 {}",TARGET_BDS_PROTOCOL_VERSION);
        logger.error("这可能导致未知错误或引起服务端崩溃，请更换适配的插件版本。");
        MessageBox(NULL,TEXT("不兼容的BDS版本！\n\n请更换适配的插件版本或使用适配的BDS版本。"),TEXT("DespawnLags"),MB_ICONERROR | MB_OK);
    }
    else{
        PluginInit();
    }

#endif
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        ll::registerPlugin(
            PLUGIN_NAME,
            PLUGIN_INTRODUCTION,
            ll::Version(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_LLVERSION_STATUS),
            std::map<std::string, std::string>{
                {"Author", PLUGIN_AUTHOR},
            });
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C"
{
    _declspec(dllexport) void onPostInit()
    {
        std::ios::sync_with_stdio(false);
        CheckProtocolVersion();
    }
}
