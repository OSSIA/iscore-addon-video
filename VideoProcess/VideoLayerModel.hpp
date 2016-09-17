#pragma once
#include <VideoProcess/VideoModel.hpp>
#include <Process/LayerModel.hpp>

namespace Video
{
using Layer = Process::LayerModel_T<ProcessModel>;
}

LAYER_METADATA(
        ,
        Video::Layer,
        "8a28108c-4a22-4576-a320-bcea75289ce4",
        "VideoLayer",
        "VideoLayer"
        )
