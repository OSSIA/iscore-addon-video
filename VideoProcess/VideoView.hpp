#pragma once
#include <Process/LayerView.hpp>
#include <QString>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>

class QGraphicsItem;
class QPainter;
//class QQuickWidget;

namespace Video
{
class VideoView final : public Process::LayerView
{
        Q_OBJECT
    public:
        explicit VideoView(QGraphicsItem* parent);

        void setVideo(const QString& video);


        QMediaPlayer player;
    private:
        void paint_impl(QPainter*) const override;
};
}
