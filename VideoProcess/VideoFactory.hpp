#pragma once
#include <Process/GenericProcessFactory.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <VideoProcess/VideoProcessMetadata.hpp>
#include <VideoProcess/VideoLayerModel.hpp>
#include <VideoProcess/VideoPresenter.hpp>
#include <VideoProcess/VideoView.hpp>
#include <Process/LayerModelPanelProxy.hpp>
namespace Video
{

using ProcessFactory = Process::ProcessFactory_T<
    Video::ProcessModel>;

using LayerFactory = Process::LayerFactory_T<
Video::ProcessModel,
Video::VideoPresenter,
Video::VideoView,
Process::GraphicsViewLayerPanelProxy>;

}


