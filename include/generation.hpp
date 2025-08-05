#pragma once

#include "block.hpp"
#include "FastNoiseLite.hpp"

#include <cmath>

#include <glm/vec3.hpp>


namespace generation
{
inline Block genBlockAt(glm::ivec3 at)
{
    // INEFFICIENT
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);

    Block result = BlockTypes::getBlockById(static_cast<size_t>(BLOCK::DIRT));

    if(at.y >= pow(noise.GetNoise((float)at.x, (float)at.z) * 4.f, 2))
        result = BlockTypes::getBlockById(static_cast<size_t>(BLOCK::AIR));

    return result;
}
} // namespace generation

