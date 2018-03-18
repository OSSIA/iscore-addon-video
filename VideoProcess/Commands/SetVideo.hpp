#pragma once
#include <VideoProcess/Commands/VideoCommandFactory.hpp>
#include <score/command/Command.hpp>
#include <score/model/path/Path.hpp>

struct DataStreamInput;
struct DataStreamOutput;
namespace Video
{
class ProcessModel;

class SetVideo final : public score::Command
{
        SCORE_COMMAND_DECL(Video::CommandFactoryName(), SetVideo, "Set a video")
    public:
        SetVideo(
            const ProcessModel& obj,
            const QString& path);

        void undo(const score::DocumentContext& ctx) const override;
        void redo(const score::DocumentContext& ctx) const override;

    protected:
        void serializeImpl(DataStreamInput & s) const override;
        void deserializeImpl(DataStreamOutput & s) override;

    private:
        Path<ProcessModel> m_model;
        QString m_old, m_new;
};

}
