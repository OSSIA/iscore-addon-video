#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>
#include <QJsonObject>
#include <QJsonValue>
#include <algorithm>

#include "VideoLayerModel.hpp"
#include "VideoModel.hpp"
#include <State/Address.hpp>
#include <score/serialization/JSONValueVisitor.hpp>
#include <score/serialization/VisitorCommon.hpp>

template <>
void DataStreamReader::read(const Video::ProcessModel& video)
{
    m_stream << video.file().path;

    insertDelimiter();
}

template <>
void DataStreamWriter::write(Video::ProcessModel& video)
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
void JSONObjectWriter::write(Video::ProcessModel& video)
{
    video.setFile(Video::VideoFile{obj[strings.Path].toString()});
}
