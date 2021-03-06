﻿#pragma once
#include <Process/Process.hpp>
#include <State/Address.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <QByteArray>
#include <QString>

#include <Process/TimeValue.hpp>
#include <score/serialization/VisitorInterface.hpp>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include <QUrl>

class DataStream;
class JSONObject;
namespace Process { class ProcessModel; }
class QObject;
#include <Process/Execution/ProcessComponent.hpp>
#include <score/model/Identifier.hpp>
#include <score_addon_video_export.h>


namespace Video
{
struct VideoFile
{
        QString path;
};

class SCORE_ADDON_VIDEO_EXPORT ProcessModel final : public Process::ProcessModel
{
        SCORE_SERIALIZE_FRIENDS
        PROCESS_METADATA_IMPL(Video::ProcessModel)

        W_OBJECT(ProcessModel)

    public:
        ProcessModel(const TimeVal& duration,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);

        template<typename Impl>
        ProcessModel(Impl& vis, QObject* parent) :
            Process::ProcessModel{vis, parent}
        {
            vis.writeTo(*this);
        }

        //// VideoModel specifics ////
        VideoFile file() const
        { return m_video; }
        void setFile(const VideoFile& path)
        {
            m_video = path;
            videoChanged();
        }

        void videoChanged() W_SIGNAL(videoChanged);

        void play() W_SIGNAL(play);
        void pause() W_SIGNAL(pause);
        void resume() W_SIGNAL(resume);
        void stop() W_SIGNAL(stop);
        void setSpeed(double speed) W_SIGNAL(setSpeed, speed);
        void seek(qint64 pos) W_SIGNAL(seek, pos);

    private:
        void stopExecution() override;
        VideoFile m_video;

};

class Executor final :
        public ::Execution::ProcessComponent_T<Video::ProcessModel, Video::Executor>
{
        COMPONENT_METADATA("a8829dcd-09a9-48e5-bd47-8e0164eef2a5")
    public:
        Executor(
                ProcessModel& element,
                const Execution::Context& ctx,
                const Id<score::Component>& id,
                QObject* parent);
};
using ComponentFactory = ::Execution::ProcessComponentFactory_T<Executor>;
}

