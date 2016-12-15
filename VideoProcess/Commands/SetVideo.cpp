#include <VideoProcess/VideoModel.hpp>

#include "SetVideo.hpp"
#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/model/path/PathSerialization.hpp>
namespace Video
{
SetVideo::SetVideo(
    Path<ProcessModel>&& model,
    const QString& text):
  m_model{std::move(model)},
  m_new{text}
{
    m_old = m_model.find().file().path;
}

void SetVideo::undo() const
{
    m_model.find().setFile(VideoFile{m_old});
}

void SetVideo::redo() const
{
    m_model.find().setFile(VideoFile{m_new});

}

void SetVideo::serializeImpl(DataStreamInput& s) const
{
    s << m_model << m_old << m_new;
}

void SetVideo::deserializeImpl(DataStreamOutput& s)
{
    s >> m_model >> m_old >> m_new;
}

}
