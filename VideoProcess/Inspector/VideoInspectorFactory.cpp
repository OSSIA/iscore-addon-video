#include <QString>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include "VideoInspectorFactory.hpp"
#include "VideoInspectorWidget.hpp"
#include <VideoProcess/VideoModel.hpp>
class InspectorWidgetBase;
class QObject;
class QWidget;
namespace iscore {
class Document;
}

namespace Video
{
Process::InspectorWidgetDelegate* InspectorFactory::make(
        const Process::ProcessModel& process,
        const iscore::DocumentContext& doc,
        QWidget* parent) const
{
    return new InspectorWidget{
        static_cast<const ProcessModel&>(process), doc, parent};
}

bool InspectorFactory::matches(const Process::ProcessModel& process) const
{
    return dynamic_cast<const ProcessModel*>(&process);
}
}
