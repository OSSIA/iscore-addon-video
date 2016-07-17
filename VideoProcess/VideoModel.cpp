#include <iscore/tools/std/Optional.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <QDebug>
#include <Editor/State.h>
#include <QPoint>
#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <Process/ModelMetadata.hpp>
#include <iscore/tools/IdentifiedObjectMap.hpp>
#include <iscore/tools/SettableIdentifier.hpp>

namespace Process { class LayerModel; }
namespace Process { class ProcessModel; }
class QObject;
namespace Video
{
ProcessModel::ProcessModel(
        const TimeValue& duration,
        const Id<Process::ProcessModel>& id,
        QObject* parent) :
    Process::ProcessModel {duration, id, Metadata<ObjectKey_k, ProcessModel>::get(), parent}
{
    metadata.setName(QString("Video.%1").arg(*this->id().val()));
    setFile(VideoFile{"/tmp/BadApple.mp4"});
}

ProcessModel::ProcessModel(
        const ProcessModel& source,
        const Id<Process::ProcessModel>& id,
        QObject* parent):
    Process::ProcessModel {source, id, Metadata<ObjectKey_k, ProcessModel>::get(), parent},
    m_video(source.m_video)
{
    metadata.setName(QString("Video.%1").arg(*this->id().val()));
}

void ProcessModel::stopExecution()
{
    // used to stop video on global stop
    // TODO get rid of this
    emit execution(false);
}
}

#include <Editor/TimeConstraint.h>
// MOVEME
namespace Video
{
namespace Executor
{
ProcessExecutor::ProcessExecutor(ProcessModel& video):
    m_player{video}
{
}

std::shared_ptr<OSSIA::StateElement> ProcessExecutor::state()
{
    return state(parent->getPosition());
}

std::shared_ptr<OSSIA::StateElement> ProcessExecutor::state(double t)
{
    auto st = OSSIA::State::create();
    if(t == 0)
    {
        m_player.play();
    }
    else if(t >= 1)
    {
        m_player.stop();
    }
    return st;
}

std::shared_ptr<OSSIA::StateElement> ProcessExecutor::offset(
        const OSSIA::TimeValue& off)
{
    return state(off / parent->getDurationNominal());
}

Component::Component(
        ::RecreateOnPlay::ConstraintElement& parentConstraint,
        ProcessModel& element,
        const ::RecreateOnPlay::Context& ctx,
        const Id<iscore::Component>& id,
        QObject* parent):
    ::RecreateOnPlay::ProcessComponent_T<Video::ProcessModel>{parentConstraint, element, ctx, id, "VideoComponent", parent}
{
    auto proc = std::make_shared<ProcessExecutor>(element);
    m_ossia_process = proc;
}
}
}
