#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>

enum class RESULT_CODE
{
    CODE_NO_ERROR,
    CODE_ERROR,
    CODE_FATAL_ERROR
};

typedef std::vector<int> Direction;

enum class Directions
{
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    UP,
    DOWN,
};

inline std::vector<int> getDirection(Directions dir)
{
    std::vector<int> result;

    switch (dir)
    {
    case Directions::FRONT:
        result = {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0};
        break;

    case Directions::BACK:
        result = {1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
        break;

    case Directions::RIGHT:
        result = {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1};
        break;

    case Directions::LEFT:
        result = {
            1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
        };
        break;

    case Directions::UP:
        result = {
            0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        };
        break;

    case Directions::DOWN:
        result = {
            0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
        };
        break;
    }

    return result;
}

inline std::vector<int> getUvCoordinates(Directions dir)
{
    std::vector<int> result;

    switch (dir)
    {
    case Directions::FRONT:
        result = {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0};
        break;

    case Directions::BACK:
        result = {1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
        break;

    case Directions::RIGHT:
        result = {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1};
        break;

    case Directions::LEFT:
        result = {
            1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
        };
        break;

    case Directions::UP:
        result = {
            0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        };
        break;

    case Directions::DOWN:
        result = {
            0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
        };
        break;
    }

    return result;
}

inline void printVector(glm::vec3 vec)
{
    std::cout << "[INFO] | " << "X: " << vec.x << ", Y: " << vec.y << ", Z:" << vec.z;
}
