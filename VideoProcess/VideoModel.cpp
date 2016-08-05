#include <iscore/tools/std/Optional.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <QDebug>
#include <ossia/editor/state/state_element.hpp>
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

#include <ossia/editor/scenario/time_constraint.hpp>
// MOVEME
namespace Video
{
namespace Executor
{
ProcessExecutor::ProcessExecutor(ProcessModel& video):
    m_player{video}
{
}

ossia::state_element ProcessExecutor::state()
{
    return state(parent->getPosition());
}

ossia::state_element ProcessExecutor::state(double t)
{
    // TODO instead use associated states processes to start and stop them.
    if(t == 0)
    {
        m_player.play();
    }
    else if(t >= 1)
    {
        m_player.stop();
    }
    return {};
}

ossia::state_element ProcessExecutor::offset(
        ossia::time_value off)
{
    return state(off / parent->getDurationNominal());
}

Component::Component(
        ::RecreateOnPlay::ConstraintElement& parentConstraint,
        ProcessModel& element,
        const ::RecreateOnPlay::Context& ctx,
        const Id<iscore::Component>& id,
        QObject* parent):
    ::RecreateOnPlay::ProcessComponent_T<Video::ProcessModel, ProcessExecutor>{parentConstraint, element, ctx, id, "VideoComponent", parent}
{
    auto proc = new ProcessExecutor(element);
    m_ossia_process = proc;
}
}
}
