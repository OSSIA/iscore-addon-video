#pragma once
#include <Process/LayerPresenter.hpp>
#include <VideoProcess/VideoLayerModel.hpp>
#include <QPoint>

#include <Process/ZoomHelper.hpp>
#include <score/model/Identifier.hpp>
#include <Process/Focus/FocusDispatcher.hpp>

namespace Video
{
class VideoView;
class ProcessModel;
class VideoPresenter final :
        public Process::LayerPresenter
{
    public:
        explicit VideoPresenter(
                const ProcessModel& model,
                VideoView* view,
                const Process::ProcessPresenterContext& ctx,
                QObject* parent);

        void setWidth(qreal width) override;
        void setHeight(qreal height) override;

        void putToFront() override;
        void putBehind() override;

        void on_zoomRatioChanged(ZoomRatio) override;

        void parentGeometryChanged() override;

        const Process::ProcessModel& model() const override;
        const Id<Process::ProcessModel>& modelId() const override;

    private:
        const ProcessModel& m_layer;
        VideoView* m_view{};
};
}
