#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/serialization/JSONVisitor.hpp>
template <typename T> class Reader;
template <typename T> class Writer;

namespace Video
{
class Layer;
}
/////// ViewModel
template<>
void Visitor<Reader<DataStream>>::readFrom(const Video::Layer& lm)
{
}

template<>
void Visitor<Writer<DataStream>>::writeTo(Video::Layer& lm)
{
}



template<>
void Visitor<Reader<JSONObject>>::readFrom(const Video::Layer& lm)
{
}

template<>
void Visitor<Writer<JSONObject>>::writeTo(Video::Layer& lm)
{
}
