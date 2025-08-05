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
        noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Cellular);

        noise.SetFrequency(0.015);
        noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
        noise.SetFractalOctaves(2);
        noise.SetFractalLacunarity(2.350);
        noise.SetFractalGain(0.650);
        noise.SetFractalWeightedStrength(0.390);

        noise.SetCellularDistanceFunction(
            FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_EuclideanSq);
        noise.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_Distance);
        noise.SetCellularJitter(1.710);
    }

    Block result = BlockTypes::getBlockById(BLOCK::DIRT);

    if (at.y >= pow(noise.GetNoise((float)at.x, (float)at.z) * 2.f, 6))
        result = BlockTypes::getBlockById(BLOCK::AIR);

    return result;
}
} // namespace generation
