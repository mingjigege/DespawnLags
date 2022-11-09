#include "setting.h"
#include "Global.h"
#include <llapi/mc/ItemStack.hpp>

int i;

void DespawnLags(){
    auto task = Schedule::repeat([]{
        auto allentities = Global<Level>->getAllEntities(); 
        if(allentities.size() >= 1){
            for(i = 0 ; i <= allentities.size()-1 ; i++){
                auto en = allentities[i];
                if(en->isItemActor() == true){
                    auto it = (ItemActor*)en;
                    auto itemtype = it->getItemStack()->getTypeName();
                    if(!Settings::ItemList.count(itemtype)){
                        if(it->getLatestSpawnTime() <= 20){
                            it->setDespawnTime(Settings::DespawnSeconds);
                        }
                    }
                }
            }
        }
    },20);
}