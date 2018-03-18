#pragma once
#include <Process/Inspector/ProcessInspectorWidgetDelegate.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <QString>
#include <score/command/Dispatchers/CommandDispatcher.hpp>

namespace score{
class Document;
struct DocumentContext;
}
class QLabel;
class QComboBox;
class QPushButton;

namespace Video
{
class ProcessModel;
class InspectorWidget final :
        public Process::InspectorWidgetDelegate_T<Video::ProcessModel>
{
    public:
        explicit InspectorWidget(
                const ProcessModel& object,
                const score::DocumentContext& context,
                QWidget* parent);

    private:
        QLabel* m_label{};
        QPushButton* m_loadButton{};
        CommandDispatcher<> m_dispatcher;
};
}
