#include "setting.h"
#include "Global.h"
#include <llapi/LoggerAPI.h>

void loadConfig() {
    if (!std::filesystem::exists("plugins/DespawnLags"))
        std::filesystem::create_directories("plugins/DespawnLags");	
    if (std::filesystem::exists(ConfigFile)) {
        Settings::LoadConfigFromJson(ConfigFile);
    }
    else {
        logger.warn("配置文件不存在，已自动创建");
        Settings::WriteDefaultConfig(ConfigFile);
    }
    if(Settings::DespawnSeconds < 20){
        logger.warn("掉落物存在时间不能少于20刻!已自动设置为20刻。");
        Settings::DespawnSeconds = 20;
        Settings::reloadJson(ConfigFile);
    }
    if(Settings::DespawnSeconds > 2147483647){
        logger.warn("掉落物存在时间不能大于2147483647刻!已自动设置为2147483647刻。");
        Settings::DespawnSeconds = 2147483647;
        Settings::reloadJson(ConfigFile);
    }
}