#include "layer_defines.h"

uint64_t LayerIdToMask(int layerId)
{
    if ((layerId < (int) LAYER_ID::BOTTOM) || (layerId > (int) LAYER_ID::TOP))
        return 0;

    return (uint64_t) 1 << layerId;
}
