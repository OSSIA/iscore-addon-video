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

using ProcessFactory = Process::GenericProcessFactory<
    Video::ProcessModel,
    Video::Layer,
    Video::VideoPresenter,
    Video::VideoView,
    Process::GraphicsViewLayerModelPanelProxy>;

}


