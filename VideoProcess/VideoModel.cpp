#include <iscore/tools/std/Optional.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <QDebug>
#include <QPoint>

#include <VideoProcess/VideoProcessMetadata.hpp>
#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <Process/ModelMetadata.hpp>
#include <iscore/plugins/documentdelegate/plugin/ElementPluginModelList.hpp>
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
    pluginModelList = new iscore::ElementPluginModelList{iscore::IDocument::documentContext(*parent), this};

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
    pluginModelList = new iscore::ElementPluginModelList(*source.pluginModelList, this);

    metadata.setName(QString("Video.%1").arg(*this->id().val()));
}

Process::ProcessModel* ProcessModel::clone(
        const Id<Process::ProcessModel>& newId,
        QObject* newParent) const
{
    return new ProcessModel {*this, newId, newParent};
}

UuidKey<Process::ProcessFactory>ProcessModel::concreteFactoryKey() const
{
    return Metadata<ConcreteFactoryKey_k, ProcessModel>::get();
}

QString ProcessModel::prettyName() const
{
    return metadata.name();
}

void ProcessModel::setDurationAndScale(const TimeValue& newDuration)
{
    // We only need to change the duration.
    setDuration(newDuration);
}

void ProcessModel::setDurationAndGrow(const TimeValue& newDuration)
{
    setDuration(newDuration);
}

void ProcessModel::setDurationAndShrink(const TimeValue& newDuration)
{
    setDuration(newDuration);
}

Process::LayerModel* ProcessModel::makeLayer_impl(
        const Id<Process::LayerModel>& viewModelId,
        const QByteArray& constructionData,
        QObject* parent)
{
    auto vm = new LayerModel{*this, viewModelId, parent};
    return vm;
}

Process::LayerModel* ProcessModel::cloneLayer_impl(
        const Id<Process::LayerModel>& newId,
        const Process::LayerModel& source,
        QObject* parent)
{
    auto vm = new LayerModel {
              static_cast<const LayerModel&>(source), *this, newId, parent};
    return vm;
}

ProcessStateDataInterface* ProcessModel::startStateData() const
{
    return nullptr;
}

ProcessStateDataInterface* ProcessModel::endStateData() const
{
    return nullptr;
}

void ProcessModel::startExecution()
{
    emit execution(true);
}

void ProcessModel::stopExecution()
{
    emit execution(false);
}

void ProcessModel::reset()
{
}

Selection ProcessModel::selectableChildren() const
{
    return {};
}

Selection ProcessModel::selectedChildren() const
{
    return {};
}

void ProcessModel::setSelection(const Selection& s) const
{
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

ProcessComponent::ProcessComponent(
        RecreateOnPlay::ConstraintElement& parentConstraint,
        ProcessModel& element,
        const RecreateOnPlay::Context& ctx,
        const Id<iscore::Component>& id,
        QObject* parent):
    RecreateOnPlay::ProcessComponent{parentConstraint, element, id, "VideoComponent", parent}
{
    auto proc = std::make_shared<ProcessExecutor>(element);
    m_ossia_process = proc;
}

const iscore::Component::Key& ProcessComponent::key() const
{
    static iscore::Component::Key k("VideoComponent");
    return k;
}

ProcessComponentFactory::~ProcessComponentFactory()
{

}

RecreateOnPlay::ProcessComponent* ProcessComponentFactory::make(
        RecreateOnPlay::ConstraintElement& cst,
        Process::ProcessModel& proc,
        const RecreateOnPlay::Context& ctx,
        const Id<iscore::Component>& id,
        QObject* parent) const
{
    return new ProcessComponent{cst, static_cast<ProcessModel&>(proc), ctx, id, parent};
}

const ProcessComponentFactory::ConcreteFactoryKey&
ProcessComponentFactory::concreteFactoryKey() const
{
    static ConcreteFactoryKey k("76a6947c-5e41-4056-8531-5a47cef035d3");
    return k;
}

bool ProcessComponentFactory::matches(
        Process::ProcessModel& proc,
        const RecreateOnPlay::DocumentPlugin&,
        const iscore::DocumentContext&) const
{
    return dynamic_cast<ProcessModel*>(&proc);
}
}
}
