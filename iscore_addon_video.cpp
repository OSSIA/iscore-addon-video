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

#if defined(ISCORE_LIB_INSPECTOR)
#include <VideoProcess/Inspector/VideoInspectorFactory.hpp>
#endif

#include <iscore_addon_video_commands_files.hpp>
#include <VideoProcess/VideoFactory.hpp>

iscore_addon_video::iscore_addon_video() :
    QObject {}
{
}

iscore_addon_video::~iscore_addon_video()
{

}


std::vector<std::unique_ptr<iscore::FactoryInterfaceBase>> iscore_addon_video::factories(
        const iscore::ApplicationContext& ctx,
        const iscore::AbstractFactoryKey& key) const
{
    return instantiate_factories<
            iscore::ApplicationContext,
    TL<
        FW<Process::ProcessFactory,
             Video::ProcessFactory>,
        FW<Process::InspectorWidgetDelegateFactory,
             Video::InspectorFactory>,
        FW<RecreateOnPlay::ProcessComponentFactory,
             Video::Executor::ProcessComponentFactory>
    >>(ctx, key);
}

std::pair<const CommandParentFactoryKey, CommandGeneratorMap> iscore_addon_video::make_commands()
{
    using namespace Video;
    std::pair<const CommandParentFactoryKey, CommandGeneratorMap> cmds{CommandFactoryName(), CommandGeneratorMap{}};

    using Types = TypeList<
#include <iscore_addon_video_commands.hpp>
      >;
    for_each_type<Types>(iscore::commands::FactoryInserter{cmds.second});

    return cmds;
}

iscore::Version iscore_addon_video::version() const
{
    return iscore::Version{1};
}

UuidKey<iscore::Plugin> iscore_addon_video::key() const
{
    return "5f2cd9ce-5744-467a-a53a-beb0e8c10ebe";
}
