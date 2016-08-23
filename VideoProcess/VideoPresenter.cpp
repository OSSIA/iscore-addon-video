#include <Process/LayerModel.hpp>
#include <Process/Process.hpp>

#include "VideoPresenter.hpp"
#include "VideoView.hpp"
#include <VideoProcess/VideoModel.hpp>
#include <VideoProcess/VideoLayerModel.hpp>
#include <Process/LayerPresenter.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <iscore/document/DocumentContext.hpp>
class QMenu;
class QObject;


namespace Video
{
VideoPresenter::VideoPresenter(
        const Layer& layer,
        VideoView* view,
        const Process::ProcessPresenterContext& ctx,
        QObject* parent):
    LayerPresenter{ctx, parent},
    m_layer{layer},
    m_view{view}
{
    putToFront();

    auto& model = layer.processModel();
    con(model.metadata, &ModelMetadata::NameChanged,
            this, [&] (QString s)
    {
        putToFront();
    });

    con(model, &ProcessModel::videoChanged,
        this, [&] ( ) {
        m_view->setVideo(m_layer.processModel().file().path);
    });

    con(model, &ProcessModel::play, this, [=] { view->player.play(); });
    con(model, &ProcessModel::pause, this, [=] { view->player.pause(); });
    con(model, &ProcessModel::resume, this, [=] { view->player.play(); });
    con(model, &ProcessModel::stop, this, [=] { view->player.stop(); });
    con(model, &ProcessModel::seek, this, [=] (auto pos) { view->player.setPosition(pos); });
    con(model, &ProcessModel::setSpeed, this, [=] (auto rate) { view->player.setPlaybackRate(rate); });

    con(model, &ProcessModel::execution, this, [=] (bool b) { if(!b) view->player.stop(); });
    m_view->setVideo(model.file().path);
}

void VideoPresenter::setWidth(qreal val)
{
    m_view->setWidth(val);
}

void VideoPresenter::setHeight(qreal val)
{
    m_view->setHeight(val);
}

void VideoPresenter::putToFront()
{
    m_view->setOpacity(1.);
}

void VideoPresenter::putBehind()
{
    m_view->setOpacity(0.8);
}

void VideoPresenter::on_zoomRatioChanged(ZoomRatio)
{
}

void VideoPresenter::parentGeometryChanged()
{
}

const Process::LayerModel& VideoPresenter::layerModel() const
{
    return m_layer;
}

const Id<Process::ProcessModel>& VideoPresenter::modelId() const
{
    return m_layer.processModel().id();
}

}
