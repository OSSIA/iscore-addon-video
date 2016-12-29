#include <iscore/tools/std/Optional.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <QDebug>
#include <ossia/editor/state/state_element.hpp>
#include <QPoint>
#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <iscore/model/ModelMetadata.hpp>
#include <iscore/model/IdentifiedObjectMap.hpp>
#include <iscore/model/Identifier.hpp>

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
    metadata().setInstanceName(*this);
    setFile(VideoFile{"/tmp/BadApple.mp4"});
}

ProcessModel::ProcessModel(
        const ProcessModel& source,
        const Id<Process::ProcessModel>& id,
        QObject* parent):
    Process::ProcessModel {source, id, Metadata<ObjectKey_k, ProcessModel>::get(), parent},
    m_video(source.m_video)
{
    metadata().setInstanceName(*this);
}

void ProcessModel::stopExecution()
{
    // used to stop video on global stop
    // TODO get rid of this
    qDebug("dem stops");
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
    return {};
}

void ProcessExecutor::start()
{
  // TODO we should play the video and hide it if it is muted.
  if(unmuted())
    m_player.play();
}

void ProcessExecutor::stop()
{
    m_player.stop();
}

void ProcessExecutor::pause()
{
    m_player.pause();
}

void ProcessExecutor::resume()
{
    m_player.resume();
}

ossia::state_element ProcessExecutor::offset(
        ossia::time_value off)
{
    m_player.seek(off);
    return {};
}

Component::Component(
        ::Engine::Execution::ConstraintElement& parentConstraint,
        ProcessModel& element,
        const ::Engine::Execution::Context& ctx,
        const Id<iscore::Component>& id,
        QObject* parent):
    ::Engine::Execution::ProcessComponent_T<Video::ProcessModel, ProcessExecutor>{parentConstraint, element, ctx, id, "VideoComponent", parent}
{
    auto proc = new ProcessExecutor(element);
    m_ossia_process = proc;
}
}
}
