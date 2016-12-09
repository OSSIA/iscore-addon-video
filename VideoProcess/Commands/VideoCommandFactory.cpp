#include "VideoCommandFactory.hpp"
#include <iscore/command/Command.hpp>

namespace Video
{
const CommandParentFactoryKey& CommandFactoryName() {
    static const CommandParentFactoryKey key{"Video"};
    return key;
}
}
