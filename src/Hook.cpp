#include "setting.h"
#include <HookAPI.h>
#include <mc/Actor.hpp>
#include <mc/ItemActor.hpp>
#include <mc/Level.hpp>
#include <mc/BlockSource.hpp>
#include <mc/ItemStack.hpp>
#include <mc/Spawner.hpp>
#include <mc/Vec3.hpp>

TInstanceHook(ItemActor*, "?spawnItem@Spawner@@QEAAPEAVItemActor@@AEAVBlockSource@@AEBVItemStack@@PEAVActor@@AEBVVec3@@H@Z", Spawner, BlockSource& a1, ItemStack& a2, Actor* a3, Vec3& a4, int a5) {
    auto it = original(this, a1, a2, a3, a4, a5);
    auto itemtype = it->getItemStack()->getTypeName();
    if(!Settings::ItemList.count(itemtype)){
        it->setDespawnTime(Settings::DespawnSeconds);
    }
    return it;
}