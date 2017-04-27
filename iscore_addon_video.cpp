#include <VideoProcess/VideoLayerModel.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <unordered_map>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include <VideoProcess/Commands/VideoCommandFactory.hpp>
#include <Inspector/InspectorWidgetFactoryInterface.hpp>
#include <Process/ProcessFactory.hpp>
#include <Process/Inspector/ProcessInspectorWidgetDelegate.hpp>
#include <iscore/plugins/customfactory/StringFactoryKey.hpp>
#include <iscore/plugins/customfactory/FactorySetup.hpp>
#include "iscore_addon_video.hpp"

#include <VideoProcess/Inspector/VideoInspectorFactory.hpp>

#include <iscore_addon_video_commands_files.hpp>
#include <VideoProcess/VideoFactory.hpp>

iscore_addon_video::iscore_addon_video() :
    QObject {}
{
}

iscore_addon_video::~iscore_addon_video()
{

}


std::vector<std::unique_ptr<iscore::InterfaceBase>> iscore_addon_video::factories(
        const iscore::ApplicationContext& ctx,
        const iscore::InterfaceKey& key) const
{
    return instantiate_factories<
            iscore::ApplicationContext,
        FW<Process::ProcessModelFactory,
           Video::ProcessFactory>,
        FW<Process::InspectorWidgetDelegateFactory,
             Video::InspectorFactory>,
        FW<Engine::Execution::ProcessComponentFactory,
             Video::Executor::ComponentFactory>
    >(ctx, key);
}

std::pair<const CommandGroupKey, CommandGeneratorMap> iscore_addon_video::make_commands()
{
    using namespace Video;
    std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{CommandFactoryName(), CommandGeneratorMap{}};

    using Types = TypeList<
#include <iscore_addon_video_commands.hpp>
      >;
    for_each_type<Types>(iscore::commands::FactoryInserter{cmds.second});

    return cmds;
}
