#include <VideoProcess/VideoLayerModel.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <unordered_map>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include <VideoProcess/Commands/VideoCommandFactory.hpp>
#include <Inspector/InspectorWidgetFactoryInterface.hpp>
#include <Process/ProcessFactory.hpp>
#include <Process/Inspector/ProcessInspectorWidgetDelegate.hpp>
#include <score/plugins/StringFactoryKey.hpp>
#include <score/plugins/FactorySetup.hpp>
#include "score_addon_video.hpp"

#include <VideoProcess/Inspector/VideoInspectorFactory.hpp>

#include <score_addon_video_commands_files.hpp>
#include <VideoProcess/VideoFactory.hpp>

#include <wobjectimpl.h>

score_addon_video::score_addon_video()
{
}

score_addon_video::~score_addon_video()
{
}


std::vector<std::unique_ptr<score::InterfaceBase>> score_addon_video::factories(
        const score::ApplicationContext& ctx,
        const score::InterfaceKey& key) const
{
    return instantiate_factories<
            score::ApplicationContext,
        FW<Process::ProcessModelFactory,
           Video::ProcessFactory>,
        FW<Process::InspectorWidgetDelegateFactory,
             Video::InspectorFactory>
      // , FW<Engine::Execution::ProcessComponentFactory,
      //      Video::Executor::ComponentFactory>
    >(ctx, key);
}

std::pair<const CommandGroupKey, CommandGeneratorMap> score_addon_video::make_commands()
{
    using namespace Video;
    std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{CommandFactoryName(), CommandGeneratorMap{}};

    ossia::for_each_type<
      #include <score_addon_video_commands.hpp>
        >(score::commands::FactoryInserter{cmds.second});

    return cmds;
}


#include <score/plugins/PluginInstances.hpp>
SCORE_EXPORT_PLUGIN(score_addon_video)
