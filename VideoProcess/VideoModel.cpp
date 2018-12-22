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
#include <ossia/dataflow/graph_node.hpp>
#include <ossia/dataflow/node_process.hpp>
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

class Process : public ossia::node_process
{
public:
  Process(ProcessModel& p, ossia::node_ptr n)
    : ossia::node_process{n}
    , m_player{p}
  {

  }
  void start() override
  {
    if(unmuted())
      m_player.play();
  }
  void stop() override
  {
    m_player.stop();
  }
  void pause() override
  {
    m_player.pause();
  }
  void resume() override
  {
    m_player.resume();
  }
private:
  ProcessModel& m_player;

  // time_process interface
public:
  void offset(ossia::time_value date, double pos) override
  {
    m_player.seek(date);
  }
  void transport(ossia::time_value date, double pos) override
  {
    m_player.seek(date);
  }
};

class Node : public ossia::graph_node
{

};

Executor::Executor(
        ProcessModel& element,
        const ::Execution::Context& ctx,
        const Id<score::Component>& id,
        QObject* parent):
    Execution::ProcessComponent_T<Video::ProcessModel, Executor>{element, ctx, id, "VideoComponent", parent}
{
  auto node = std::make_shared<Node>();
  auto proc = std::make_shared<Process>(element, node);
  m_ossia_process = proc;
}
}
