#pragma once
#include <Process/ProcessMetadata.hpp>
#include <QString>
#include <score/plugins/customfactory/UuidKey.hpp>
#include <score_addon_video_export.h>

namespace Video
{
class ProcessModel;
}

PROCESS_METADATA(
        SCORE_ADDON_VIDEO_EXPORT,
        Video::ProcessModel,
        "47e767b3-af0c-4c8e-aaf4-c28d951966fa",
        "Video",
        "Video",
    "Graphics",
    {},
    Process::ProcessFlags::SupportsTemporal |
    Process::ProcessFlags::PutInNewSlot
        )
