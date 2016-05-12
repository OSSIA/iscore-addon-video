#pragma once
#include <Process/Process.hpp>
#include <State/Address.hpp>
#include <QByteArray>
#include <QString>

#include <VideoProcess/ScaleMode.hpp>
#include <Process/TimeValue.hpp>
#include <iscore/serialization/VisitorInterface.hpp>
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

        Q_OBJECT

    public:
        ProcessModel(const TimeValue& duration,
                     const Id<Process::ProcessModel>& id,
                     QObject* parent);
        Process::ProcessModel* clone(const Id<Process::ProcessModel>& newId,
                            QObject* newParent) const override;

        template<typename Impl>
        ProcessModel(Deserializer<Impl>& vis, QObject* parent) :
            Process::ProcessModel{vis, parent}
        {
            vis.writeTo(*this);
        }

        //// ProcessModel ////
        UuidKey<Process::ProcessFactory> concreteFactoryKey() const override;

        QString prettyName() const override;

        Process::LayerModel* makeLayer_impl(
                const Id<Process::LayerModel>& viewModelId,
                const QByteArray& constructionData,
                QObject* parent) override;
        Process::LayerModel* loadLayer_impl(
                const VisitorVariant&,
                QObject* parent) override;

        void setDurationAndScale(const TimeValue& newDuration) override;
        void setDurationAndGrow(const TimeValue& newDuration) override;
        void setDurationAndShrink(const TimeValue& newDuration) override;

        void serialize_impl(const VisitorVariant& vis) const override;

        /// States
        ProcessStateDataInterface* startStateData() const override;
        ProcessStateDataInterface* endStateData() const override;

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
        Process::LayerModel* cloneLayer_impl(
                const Id<Process::LayerModel>& newId,
                const Process::LayerModel& source,
                QObject* parent) override;

    private:
        void startExecution() override;
        void stopExecution() override;
        void reset() override;

        Selection selectableChildren() const override;
        Selection selectedChildren() const override;
        void setSelection(const Selection& s) const override;

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


class ProcessComponent final : public RecreateOnPlay::ProcessComponent
{
    public:
        ProcessComponent(
                RecreateOnPlay::ConstraintElement& parentConstraint,
                ProcessModel& element,
                const RecreateOnPlay::Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent);

    private:
        const Key &key() const override;
};


class ProcessComponentFactory final :
        public RecreateOnPlay::ProcessComponentFactory
{
    public:
        virtual ~ProcessComponentFactory();

        virtual RecreateOnPlay::ProcessComponent* make(
                RecreateOnPlay::ConstraintElement& cst,
                Process::ProcessModel& proc,
                const RecreateOnPlay::Context& ctx,
                const Id<iscore::Component>& id,
                QObject* parent) const override;

        const ConcreteFactoryKey& concreteFactoryKey() const override;

        bool matches(
                Process::ProcessModel& proc,
                const RecreateOnPlay::DocumentPlugin&,
                const iscore::DocumentContext &) const override;
};


}
}

