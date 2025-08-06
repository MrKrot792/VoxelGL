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
    CRATERS,
};

constexpr GENERATION_ALGORITHM currentAlgorithm = CELLULAR;

inline Block genBlockAt(glm::ivec3 at)
{
    float power = 2.f;
    float amplitude = 4.f;

    FastNoiseLite noise;
    if (currentAlgorithm == SIMPLEX)
    {
        power = 2.f;
        amplitude = 4.f;

        noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    }
    else if (currentAlgorithm == CELLULAR)
    {
        power = 6.f;
        amplitude = 2.f;

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
    else if (currentAlgorithm == CRATERS)
    {
        power = 2.f;
        amplitude = 4.f;

        noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Cellular);

        noise.SetFrequency(0.015);
        noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
        noise.SetFractalOctaves(2);
        noise.SetFractalLacunarity(2.350);
        noise.SetFractalGain(0.650);

        noise.SetCellularDistanceFunction(
            FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_EuclideanSq);
        noise.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_Distance2Div);
    }

    Block result = BlockTypes::getBlockById(BLOCK::DIRT);

    if (at.y >= pow(noise.GetNoise((float)at.x, (float)at.z) * amplitude, power))
        result = BlockTypes::getBlockById(BLOCK::AIR);

    return result;
}
} // namespace generation
