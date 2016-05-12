#pragma once
#include <Process/LayerModelPanelProxy.hpp>
#include "VideoLayerModel.hpp"

namespace Video
{
class PanelProxy : public Process::LayerModelPanelProxy
{
    public:
        explicit PanelProxy(
                const Process::LayerModel& vm,
                QObject* parent);


        const Process::LayerModel&layer() override;
        QWidget*widget() const override;

    private:
        const Process::LayerModel& m_layer;
        QWidget* m_widget{};
};

}
