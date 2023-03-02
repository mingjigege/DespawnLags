#include <mc/ItemActor.hpp>
#include <RemoteCallAPI.h>

void SetDespawnTime(ItemActor* item, int time) {
    item->setDespawnTime(time);
}

int GetDespawnTime(ItemActor* item) {
    auto time = item->getDespawnTime();
    return time;
}

int GetSpawnTime(ItemActor* item) {
    auto time = item->getLatestSpawnTime();
    return time;
}

void ExportAPI() {
    RemoteCall::exportAs("DespawnLags","GetDespawnTime",[](ItemActor* item) -> int {return GetDespawnTime(item); });
    RemoteCall::exportAs("DespawnLags","SetDespawnTime",[](ItemActor* item, int time) -> void {return SetDespawnTime(item,time); });
    RemoteCall::exportAs("DespawnLags","GetSpawnTime",[](ItemActor* item) -> int {return GetSpawnTime(item); });
}