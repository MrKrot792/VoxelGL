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

enum class Direction
{
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    UP,
    DOWN,
};

inline std::vector<int> getDirection(Direction dir)
{
    std::vector<int> result;

    switch (dir)
    {
    case Direction::FRONT:
        result = {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0};
        break;

    case Direction::BACK:
        result = {1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
        break;

    case Direction::RIGHT:
        result = {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1};
        break;

    case Direction::LEFT:
        result = {
            1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
        };
        break;

    case Direction::UP:
        result = {
            0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        };
        break;

    case Direction::DOWN:
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
