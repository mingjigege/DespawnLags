#include <llapi/RegCommandAPI.h>
#include <llapi/DynamicCommandAPI.h>
#include "Global.h"
#include "setting.h"

using namespace RegisterCommandHelper;

void RegCommand(){
    using ParamType = DynamicCommand::ParameterType;
    auto command = DynamicCommand::createCommand(Settings::command, "设置掉落物存在时间", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0x80 }, { (CommandFlagValue)1 });
    command->setEnum("reload",{"reload"});
    command->mandatory("Reload", ParamType::Enum, "reload",CommandParameterOption::EnumAutocompleteExpansion);
    command->mandatory("DespawnTicks", ParamType::Int);
    command->addOverload({"DespawnTicks"});
    command->addOverload({"Reload"});
    command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
        if(results["DespawnTicks"].isSet){
            int sec = results["DespawnTicks"].get<int>();
            if(sec < 20){
                return output.error("掉落物存在时间不能少于20刻!");
            }
            else if(sec > 2147483647){
                return output.error("掉落物存在时间不能大于2147483647刻!");
            }
            else{
                Settings::DespawnSeconds = sec;
                Settings::reloadJson("plugins/DespawnLags/config.json");
                return output.success("设置成功");
            };
        }
        if(results["Reload"].isSet){
            Settings::LoadConfigFromJson("plugins/DespawnLags/config.json");
            return output.success("已重载插件DespawnLags");
        }
    });
    DynamicCommand::setup(std::move(command));
}