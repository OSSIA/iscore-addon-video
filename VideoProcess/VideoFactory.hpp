#pragma once

#include <Process/ProcessFactory.hpp>
#include <iscore/serialization/VisitorCommon.hpp>
#include <VideoProcess/VideoModel.hpp>
#include <VideoProcess/VideoProcessMetadata.hpp>
#include <VideoProcess/VideoLayerModel.hpp>
#include <VideoProcess/VideoPresenter.hpp>
#include <VideoProcess/VideoView.hpp>
namespace Video
{
class ProcessFactory final : public Process::ProcessFactory
{
    public:
        QString prettyName() const override
        { // In factory list
            return Metadata<PrettyName_k, ProcessModel>::get();
        }

        const UuidKey<Process::ProcessFactory>& concreteFactoryKey() const override
        {
            return Metadata<ConcreteFactoryKey_k, ProcessModel>::get();
        }


        Process::ProcessModel* makeModel(
                const TimeValue& duration,
                const Id<Process::ProcessModel>& id,
                QObject* parent) override
        {
            return new Video::ProcessModel{duration, id, parent};
        }

        QByteArray makeStaticLayerConstructionData() const override
        {
            return {};
        }

        Process::ProcessModel* load(const VisitorVariant& vis, QObject* parent) override
        {
            return deserialize_dyn(vis, [&] (auto&& deserializer)
            { return new Video::ProcessModel{deserializer, parent};});
        }

        Process::LayerPresenter* makeLayerPresenter(
                const Process::LayerModel& model,
                Process::LayerView* v,
                const Process::ProcessPresenterContext& ctx,
                QObject* parent) override
        {
            return new Video::VideoPresenter{
                dynamic_cast<const LayerModel&>(model),
                dynamic_cast<Video::VideoView*>(v),
                        ctx,
                parent};
        }

        Process::LayerView* makeLayerView(
                const Process::LayerModel&,
                QGraphicsItem* parent) override
        {
            return new Video::VideoView{parent};
        }
};

}


