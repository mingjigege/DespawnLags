#include "setting.h"
#include <HookAPI.h>
#include <mc/ItemStack.hpp>
#include <mc/ItemActor.hpp>

TClasslessInstanceHook(ItemActor *, "?spawnItem@Spawner@@QEAAPEAVItemActor@@AEAVBlockSource@@AEBVItemStack@@PEAVActor@@AEBVVec3@@H@Z", void *a1, void *a2, void *a3, void *a4, int a5)
{
    auto it = original(this, a1, a2, a3, a4, a5);
    auto itemtype = it->getItemStack()->getTypeName();
    if (itemtype == "下界岩")
    {
        it->setDespawnTime(200);
        return it;
    }
    if (!Settings::ItemList.count(itemtype))
    {
        it->setDespawnTime(Settings::DespawnSeconds);
    }
    return it;
}
