#include "VideoPanelProxy.hpp"
#include <iscore/document/DocumentContext.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <VideoProcess/VideoModel.hpp>
namespace Video
{
PanelProxy::PanelProxy(
        const Process::LayerModel& vm,
        QObject* parent):
    Process::LayerModelPanelProxy{parent},
    m_layer{vm}
{
}

const Process::LayerModel& PanelProxy::layer()
{
    return m_layer;
}

QWidget* PanelProxy::widget() const
{
    return m_widget;
}

}
