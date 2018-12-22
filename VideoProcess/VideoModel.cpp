#include <score/tools/std/Optional.hpp>
#include <score/document/DocumentInterface.hpp>
#include <QDebug>
#include <ossia/editor/state/state_element.hpp>
#include <QPoint>
#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <score/model/ModelMetadata.hpp>
#include <score/model/IdentifiedObjectMap.hpp>
#include <score/model/Identifier.hpp>
#include <wobjectimpl.h>
W_OBJECT_IMPL(Video::ProcessModel)

namespace Video
{
ProcessModel::ProcessModel(
        const TimeVal& duration,
        const Id<Process::ProcessModel>& id,
        QObject* parent) :
    Process::ProcessModel {duration, id, Metadata<ObjectKey_k, ProcessModel>::get(), parent}
{
    metadata().setInstanceName(*this);
    setFile(VideoFile{"/tmp/BadApple.mp4"});
}

void ProcessModel::stopExecution()
{
    // used to stop video on global stop
    // TODO get rid of this
    qDebug("dem stops");
    execution(false);
}
}
/*

#include <ossia/editor/scenario/time_interval.hpp>
// MOVEME
namespace Video
{
namespace Executor
{
ProcessExecutor::ProcessExecutor(ProcessModel& video):
    m_player{video}
{
}

ossia::state_element ProcessExecutor::state(ossia::time_value date, double pos)
{
    return {};
}

void ProcessExecutor::start(ossia::state&)
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
        ossia::time_value off, double pos)
{
    m_player.seek(off);
    return {};
}

Component::Component(
        ::Engine::Execution::ConstraintComponent& parentConstraint,
        ProcessModel& element,
        const ::Engine::Execution::Context& ctx,
        const Id<score::Component>& id,
        QObject* parent):
    ::Engine::Execution::ProcessComponent_T<Video::ProcessModel, ProcessExecutor>{parentConstraint, element, ctx, id, "VideoComponent", parent}
{
    auto proc = std::make_shared<ProcessExecutor>(element);
    m_ossia_process = proc;
}
}
}
*/
