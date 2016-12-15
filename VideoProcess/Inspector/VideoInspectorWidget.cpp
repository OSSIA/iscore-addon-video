#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <VideoProcess/VideoModel.hpp>
#include "VideoInspectorWidget.hpp"
#include <VideoProcess/Commands/SetVideo.hpp>
#include <Inspector/InspectorWidgetBase.hpp>
#include <iscore/command/Dispatchers/CommandDispatcher.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <iscore/model/path/Path.hpp>
#include <iscore/tools/Todo.hpp>
#include <iscore/document/DocumentContext.hpp>
#include <iscore/widgets/SignalUtils.hpp>


namespace Video
{
InspectorWidget::InspectorWidget(
        const ProcessModel& model,
        const iscore::DocumentContext& doc,
        QWidget* parent) :
    InspectorWidgetDelegate_T {model, parent},
    m_dispatcher{doc.commandStack}
{
    setObjectName("VideoInspectorWidget");
    setParent(parent);

    auto vlay = new QVBoxLayout;
    vlay->setSpacing(0);
    vlay->setContentsMargins(0,0,0,0);

    m_label = new QLabel{model.file().path, this};

    // TODO this calls for a reactive binding
    con(process(), &ProcessModel::videoChanged,
        this, [&] () {
        m_label->setText(process().file().path);
    });
    m_label->setText(process().file().path);

    m_loadButton = new QPushButton{tr("Load an video")};
    connect(m_loadButton, &QPushButton::pressed,
            this, [=] () {
        auto res = QFileDialog::getOpenFileName(
                    this,
                    tr("Load a video"),
                    "",
                    "Videos (*.mp4 *.avi *.mkv *.webm)");

        if(res == process().file().path)
            return;

        if(!QFile::exists(res))
            return;

        m_dispatcher.submitCommand(new SetVideo{process(), res});
    });

    vlay->addWidget(m_label);
    vlay->addWidget(m_loadButton);
    this->setLayout(vlay);
}
}
