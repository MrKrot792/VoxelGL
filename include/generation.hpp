#pragma once

#include "FastNoiseLite.hpp"
#include "block.hpp"

#include <cmath>

#include <glm/vec3.hpp>

namespace generation
{
enum GENERATION_ALGORITHM
{
    SIMPLEX,
    CELLULAR,
};

constexpr GENERATION_ALGORITHM currentAlgorithm = SIMPLEX;

inline Block genBlockAt(glm::ivec3 at)
{
    // INEFFICIENT
    FastNoiseLite noise;
    if (currentAlgorithm == SIMPLEX)
    {
        noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    }
    else if (currentAlgorithm == CELLULAR) 
    {
    
    }

    Block result = BlockTypes::getBlockById(BLOCK::DIRT);

    if (at.y >= pow(noise.GetNoise((float)at.x, (float)at.z) * 4.f, 2))
        result = BlockTypes::getBlockById(BLOCK::AIR);

    return result;
}
} // namespace generation
