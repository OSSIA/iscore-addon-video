#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <VideoProcess/VideoModel.hpp>
#include "VideoInspectorWidget.hpp"
#include <VideoProcess/Commands/SetVideo.hpp>
#include <Inspector/InspectorWidgetBase.hpp>
#include <score/command/Dispatchers/CommandDispatcher.hpp>
#include <score/document/DocumentInterface.hpp>
#include <score/model/path/Path.hpp>
#include <score/tools/Todo.hpp>
#include <score/document/DocumentContext.hpp>
#include <score/widgets/SignalUtils.hpp>


namespace Video
{
InspectorWidget::InspectorWidget(
        const ProcessModel& model,
        const score::DocumentContext& doc,
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

        m_dispatcher.submit(new SetVideo{process(), res});
    });

    vlay->addWidget(m_label);
    vlay->addWidget(m_loadButton);
    this->setLayout(vlay);
}
}
