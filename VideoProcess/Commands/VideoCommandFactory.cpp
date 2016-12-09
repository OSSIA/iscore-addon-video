#include "VideoCommandFactory.hpp"
#include <iscore/command/Command.hpp>

namespace Video
{
const CommandGroupKey& CommandFactoryName() {
    static const CommandGroupKey key{"Video"};
    return key;
}
}
