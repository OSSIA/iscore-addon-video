#include "VideoCommandFactory.hpp"
#include <score/command/Command.hpp>

namespace Video
{
const CommandGroupKey& CommandFactoryName() {
    static const CommandGroupKey key{"Video"};
    return key;
}
}
