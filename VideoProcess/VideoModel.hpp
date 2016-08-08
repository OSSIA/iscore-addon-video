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
        MODEL_METADATA_IMPL(Video::ProcessModel)

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
#include <Engine/Executor/ProcessElement.hpp>
#include <ossia/editor/scenario/time_value.hpp>
#include <ossia/editor/scenario/time_process.hpp>
// MOVEME
namespace Video
{
namespace Executor
{
class ProcessExecutor final :
        public ossia::time_process
{
    public:
        ProcessExecutor(ProcessModel& video);

        ossia::state_element state(double);
        ossia::state_element state() override;
        ossia::state_element offset(ossia::time_value) override;

    private:
        ProcessModel& m_player;
};


class Component final :
        public ::Engine::Execution::ProcessComponent_T<Video::ProcessModel, Video::Executor::ProcessExecutor>
{
        COMPONENT_METADATA("a8829dcd-09a9-48e5-bd47-8e0164eef2a5")
    public:
        Component(
                Engine::Execution::ConstraintElement& parentConstraint,
                ProcessModel& element,
                const Engine::Execution::Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent);
};
using ComponentFactory = ::Engine::Execution::ProcessComponentFactory_T<Component>;
}
}

