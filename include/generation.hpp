#pragma once

#include "chunk.hpp"

#include <glm/fwd.hpp>

namespace generation
{
static inline BlockData genBlockAt(glm::vec3 at)
{
    BLOCK_TYPE result = DIRT;

    if(at.y >= 0)
        result = AIR;

    if(at.y <= -40)
        result = AIR;

    if(at.x >= 30)
        result = AIR;

    return BlockData(result);
}
} // namespace generation
