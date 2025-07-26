#pragma once

#include "chunk.hpp"
#include "FastNoiseLite.hpp"

#include <cmath>
#include <glm/fwd.hpp>

namespace generation
{
inline BlockData genBlockAt(glm::ivec3 at)
{
    // INEFFICIENT
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);

    BLOCK_TYPE result = DIRT;

    if(at.y >= pow(noise.GetNoise((float)at.x, (float)at.z) * 4.f, 2))
        result = AIR;

    return BlockData(result);
}
} // namespace generation
