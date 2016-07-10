#pragma once
#include <Process/Process.hpp>
#include <State/Address.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <QByteArray>
#include <QString>

#include <Process/TimeValue.hpp>
#include <iscore/serialization/VisitorInterface.hpp>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include <QUrl>

class DataStream;
class JSONObject;
namespace Process { class LayerModel; }
namespace Process { class ProcessModel; }
class QObject;
#include <iscore/tools/SettableIdentifier.hpp>
#include <iscore_addon_video_export.h>


namespace Video
{
struct VideoFile
{
        QString path;
};

class ISCORE_ADDON_VIDEO_EXPORT ProcessModel final : public Process::ProcessModel
{
        ISCORE_SERIALIZE_FRIENDS(ProcessModel, DataStream)
        ISCORE_SERIALIZE_FRIENDS(ProcessModel, JSONObject)
        PROCESS_METADATA_IMPL(Video::ProcessModel)

        Q_OBJECT

    public:
        ProcessModel(const TimeValue& duration,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);

        template<typename Impl>
        ProcessModel(Deserializer<Impl>& vis, QObject* parent) :
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
            emit videoChanged();
        }

    signals:
        void videoChanged();

        void play();
        void pause();
        void setSpeed(double speed);
        void seek(qint64 pos);
        void stop();

    protected:
        ProcessModel(const ProcessModel& source,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);

    private:
        void stopExecution() override;
        VideoFile m_video;

};
}
#include <QMediaPlayer>
#include <OSSIA/Executor/ProcessElement.hpp>
#include <Editor/TimeValue.h>
#include <Editor/TimeProcess.h>
// MOVEME
namespace Video
{
namespace Executor
{
class ProcessExecutor final :
        public OSSIA::TimeProcess
{
    public:
        ProcessExecutor(ProcessModel& video);

        std::shared_ptr<OSSIA::StateElement> state(double);
        std::shared_ptr<OSSIA::StateElement> state() override;
        std::shared_ptr<OSSIA::StateElement> offset(const OSSIA::TimeValue &) override;

    private:
        ProcessModel& m_player;
};


class Component final :
        public ::RecreateOnPlay::ProcessComponent_T<Video::ProcessModel>
{
        COMPONENT_METADATA("a8829dcd-09a9-48e5-bd47-8e0164eef2a5")
    public:
        Component(
                RecreateOnPlay::ConstraintElement& parentConstraint,
                ProcessModel& element,
                const RecreateOnPlay::Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent);
};

EXECUTOR_PROCESS_COMPONENT_FACTORY(ComponentFactory, "9a8f11ca-f0a8-49f9-b0be-8e5dda58523e", Component, Video::ProcessModel)

}
}

