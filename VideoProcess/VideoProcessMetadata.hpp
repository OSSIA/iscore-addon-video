#pragma once
#include <Process/ProcessMetadata.hpp>
#include <QString>
#include <score/plugins/UuidKey.hpp>
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
    Process::ProcessCategory::MediaSource,
    "Graphics",
    "Graphics",
    "ossia score",
    {},
    {std::vector<Process::PortType>{Process::PortType::Message}},
    {std::vector<Process::PortType>{Process::PortType::Message}},
    Process::ProcessFlags::SupportsTemporal |
    Process::ProcessFlags::PutInNewSlot)
