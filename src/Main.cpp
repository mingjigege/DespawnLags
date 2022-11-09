#include "version.h"
#include "Global.h"
#include <llapi/EventAPI.h>
#include <llapi/LoggerAPI.h>
#include <llapi/RemoteCallAPI.h>

extern Logger logger;

extern void RegCommand();
extern void loadConfig();
extern void DespawnLags();

void SetDespawnTime(ItemActor* item, int time){
    item->setDespawnTime(time);
}

int GetDespawnTime(ItemActor* item){
    auto time = item->getDespawnTime();
    return time;
}

int GetSpawnTime(ItemActor* item){
    auto time = item->getLatestSpawnTime();
    return time;
}

void PluginInit(){
    logger.info("这个插件是免费的。如果你花钱了那一定是被坑了。");
    logger.info("当前版本 {}.{}.{}",PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION);
    logger.info("插件作者 Tsubasa6848");

    loadConfig();
    Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent) {
        RegCommand();
        DespawnLags();
        return true;
    });
    RemoteCall::exportAs("DespawnLags","GetDespawnTime",[](ItemActor* item) -> int {return GetDespawnTime(item); });
    RemoteCall::exportAs("DespawnLags","SetDespawnTime",[](ItemActor* item, int time) -> void {return SetDespawnTime(item,time); });
    RemoteCall::exportAs("DespawnLags","GetSpawnTime",[](ItemActor* item) -> int {return GetSpawnTime(item); });
}