#include "version.h"
#include "setting.h"
#include <llapi/EventAPI.h>

void PluginInit(){
    logger.info("这个插件是免费的。如果你花钱了那一定是被坑了。");
    logger.info("当前版本 {}.{}.{}",PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION);
    logger.info("插件作者 Tsubasa6848");
    loadConfig();
    ExportAPI();
    Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent) {
        RegCommand();
        return true;
    });
}