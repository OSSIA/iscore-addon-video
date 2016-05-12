#include "VideoCommandFactory.hpp"
#include <iscore/command/SerializableCommand.hpp>

namespace Video
{
const CommandParentFactoryKey& CommandFactoryName() {
    static const CommandParentFactoryKey key{"Video"};
    return key;
}
}
