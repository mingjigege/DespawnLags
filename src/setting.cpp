#include <llapi/utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "Global.h"
#include "setting.h"

#define TRJ(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \

namespace Settings {
    int DespawnSeconds = 600;
    string command = "despawntime";
    std::unordered_set<string> ItemList{
        "minecraft:netherite_helmet",
        "minecraft:netherite_chestplate",
        "minecraft:netherite_leggings",
        "minecraft:netherite_boots",
        "minecraft:netherite_sword",
        "minecraft:shulker_box",
        "minecraft:undyed_shulker_box",
        "minecraft:elytra",
        "minecraft:dragon_egg",
        "minecraft:nether_star"
    };
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["Config"]["DespawnTicks"] = DespawnSeconds;
        json["Config"]["Command"] = command;
        json["Config"]["Whitelist"] = ItemList;
        return json;
    }

    void initjson(nlohmann::json json) {
        TRJ("Config", "DespawnTicks", DespawnSeconds);
        TRJ("Config", "Command", command);
        TRJ("Config", "Whitelist", ItemList);
    }

    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            logger.error("无法打开配置文件");
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            logger.error("无法打开配置文件");
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }
    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file){
            file << globaljson().dump(4);
        }
        else{
            logger.error("配置文件异常！");
        }
        file.close();
    }
}

void loadConfig() {
    if (!std::filesystem::exists("plugins/DespawnLags"))
        std::filesystem::create_directories("plugins/DespawnLags");	
    if (std::filesystem::exists("plugins/DespawnLags/config.json")) {
        Settings::LoadConfigFromJson("plugins/DespawnLags/config.json");
    }
    else {
        logger.warn("配置文件不存在，已自动创建");
        Settings::WriteDefaultConfig("plugins/DespawnLags/config.json");
    }
    if(Settings::DespawnSeconds < 20){
        logger.warn("掉落物存在时间不能少于20刻!已自动设置为20刻。");
        Settings::DespawnSeconds = 20;
        Settings::reloadJson("plugins/DespawnLags/config.json");
    }
    if(Settings::DespawnSeconds > 2147483647){
        logger.warn("掉落物存在时间不能大于2147483647刻!已自动设置为2147483647刻。");
        Settings::DespawnSeconds = 2147483647;
        Settings::reloadJson("plugins/DespawnLags/config.json");
    }
}