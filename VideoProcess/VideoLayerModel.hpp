#pragma once
#include <VideoProcess/VideoModel.hpp>
#include <Process/LayerModel.hpp>

namespace Video
{
using Layer = Process::LayerModel_T<ProcessModel>;
}

DEFAULT_MODEL_METADATA(Video::Layer, "VideoLayer")
