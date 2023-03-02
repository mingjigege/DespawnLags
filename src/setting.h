#pragma once

#include <utils/FileHelper.h>
#include <Nlohmann/json.hpp>

namespace Settings {
    extern int DespawnSeconds;
    extern string command;
    extern std::unordered_set<string> ItemList;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void WriteDefaultConfig(const std::string& fileName);
    void LoadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
}

extern Logger logger;

extern void RegCommand();
extern void loadConfig();
extern void ExportAPI();