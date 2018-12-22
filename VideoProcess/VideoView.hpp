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
    public:
        explicit VideoView(QGraphicsItem* parent);

        void setVideo(const QString& video);


        QMediaPlayer player;

        QGraphicsVideoItem* videoItem{};
        QDialog* videoDialog{};

    private:
        void paint_impl(QPainter*) const override;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

};
}
