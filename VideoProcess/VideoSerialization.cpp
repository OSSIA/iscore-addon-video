#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/serialization/JSONVisitor.hpp>
#include <QJsonObject>
#include <QJsonValue>
#include <algorithm>

#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <State/Address.hpp>
#include <iscore/serialization/JSONValueVisitor.hpp>
#include <iscore/serialization/VisitorCommon.hpp>
#include <iscore/tools/std/StdlibWrapper.hpp>

template<>
void Visitor<Reader<DataStream>>::readFrom_impl(const Video::ProcessModel& video)
{
    m_stream << video.file().path;

    insertDelimiter();
}

template<>
void Visitor<Writer<DataStream>>::writeTo(Video::ProcessModel& video)
{
    QString path;
    m_stream >> path;

    video.setFile(Video::VideoFile{path});

    checkDelimiter();
}

template<>
void Visitor<Reader<JSONObject>>::readFrom_impl(const Video::ProcessModel& video)
{
    m_obj[iscore::StringConstant().Path] = video.file().path;
}

template<>
void Visitor<Writer<JSONObject>>::writeTo(Video::ProcessModel& video)
{
    video.setFile(Video::VideoFile{m_obj[iscore::StringConstant().Path].toString()});
}
