#include <Process/Style/ProcessFonts.hpp>
#include <QFont>
#include <qnamespace.h>
#include <QPainter>

#include "VideoView.hpp"
#include <Process/LayerView.hpp>

namespace Video
{
VideoView::VideoView(
        QGraphicsItem* parent):
    LayerView{parent}
{
    auto widg = new QGraphicsVideoItem{this};
    player.setVideoOutput(widg);
    player.setMuted(true);

}

void VideoView::setVideo(const QString &video)
{
    player.setMedia(QUrl::fromLocalFile(video));
}

void VideoView::paint_impl(QPainter* painter) const
{
}

}
