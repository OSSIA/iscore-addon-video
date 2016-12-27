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

template <>
void DataStreamReader::read(const Video::ProcessModel& video)
{
    m_stream << video.file().path;

    insertDelimiter();
}

template <>
void DataStreamWriter::writeTo(Video::ProcessModel& video)
{
    QString path;
    m_stream >> path;

    video.setFile(Video::VideoFile{path});

    checkDelimiter();
}

template <>
void JSONObjectReader::read(const Video::ProcessModel& video)
{
    obj[strings.Path] = video.file().path;
}

template <>
void JSONObjectWriter::writeTo(Video::ProcessModel& video)
{
    video.setFile(Video::VideoFile{obj[strings.Path].toString()});
}
