#pragma once
#include <Process/LayerPresenter.hpp>
#include <QPoint>

#include <Process/ZoomHelper.hpp>
#include <iscore/tools/SettableIdentifier.hpp>
#include <Process/Focus/FocusDispatcher.hpp>

namespace Process { class LayerModel; }
namespace Process { class ProcessModel; }
class QMenu;
class QObject;

namespace Video
{
class LayerModel;
class VideoView;
class VideoPresenter final :
        public Process::LayerPresenter
{
    public:
        explicit VideoPresenter(
                const LayerModel& model,
                VideoView* view,
                const Process::ProcessPresenterContext& ctx,
                QObject* parent);

        void setWidth(qreal width) override;
        void setHeight(qreal height) override;

        void putToFront() override;
        void putBehind() override;

        void on_zoomRatioChanged(ZoomRatio) override;

        void parentGeometryChanged() override;

        const Process::LayerModel& layerModel() const override;
        const Id<Process::ProcessModel>& modelId() const override;

    private:
        const LayerModel& m_layer;
        VideoView* m_view{};
};
}
