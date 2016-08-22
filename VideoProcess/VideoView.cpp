#include <Process/Style/ProcessFonts.hpp>
#include <QFont>
#include <qnamespace.h>
#include <QPainter>

#include "VideoView.hpp"
#include <QDialog>
#include <QApplication>
#include <Process/LayerView.hpp>
#include <QLayout>

#include <QGraphicsSceneMouseEvent>
#include <QVideoWidget>

namespace Video
{

struct VideoDialog : public QDialog
{
        VideoView& view;

        VideoDialog(VideoView& view, QWidget* parent):
            QDialog{parent},
            view{view}
        {
            this->setAttribute(Qt::WA_DeleteOnClose);
            auto lay = new QVBoxLayout;
            this->setLayout(lay);

            auto widg = new QVideoWidget{this};
            lay->addWidget(widg);
            view.player.setVideoOutput(widg);
        }

        void closeEvent(QCloseEvent * ev)
        {
            view.videoItem = new QGraphicsVideoItem{&view};
            view.player.setVideoOutput(view.videoItem);
            QDialog::closeEvent(ev);

        }
};

VideoView::VideoView(
        QGraphicsItem* parent):
    LayerView{parent}
{
    videoItem = new QGraphicsVideoItem{this};
    player.setVideoOutput(videoItem);
    //player.setMuted(true);

}

void VideoView::setVideo(const QString &video)
{
    player.setMedia(QUrl::fromLocalFile(video));
}

void VideoView::paint_impl(QPainter* painter) const
{
}

void VideoView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
}

void VideoView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if(!videoDialog)
    {
        delete videoItem;
        videoDialog = new VideoDialog{*this, qApp->activeWindow()};
        videoDialog->show();
    }
}

}
