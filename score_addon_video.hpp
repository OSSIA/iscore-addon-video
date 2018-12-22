#pragma once
#include <score/plugins/qt_interfaces/PluginRequirements_QtInterface.hpp>
#include <score/plugins/qt_interfaces/FactoryInterface_QtInterface.hpp>
#include <score/plugins/qt_interfaces/GUIApplicationPlugin_QtInterface.hpp>
#include <score/plugins/qt_interfaces/CommandFactory_QtInterface.hpp>
#include <QObject>
#include <utility>
#include <vector>

#include <score/application/ApplicationContext.hpp>
#include <score/command/CommandGeneratorMap.hpp>
#include <score/command/Command.hpp>
// #include <score/plugins/FactoryInterface.hpp>

class score_addon_video final :
        public score::Plugin_QtInterface,
        public score::FactoryInterface_QtInterface,
        public score::CommandFactory_QtInterface
{
  SCORE_PLUGIN_METADATA(1, "5f2cd9ce-5744-467a-a53a-beb0e8c10ebe")
    public:
        score_addon_video();
        ~score_addon_video() override;

    private:
        // Process & inspector
        std::vector<std::unique_ptr<score::InterfaceBase>> factories(
                const score::ApplicationContext& ctx,
                const score::InterfaceKey& factoryName) const override;

        // CommandFactory_QtInterface interface
        std::pair<const CommandGroupKey, CommandGeneratorMap> make_commands() override;
};
