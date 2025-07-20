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

struct Directions
{
    static inline const std::vector<int> FRONT = {-1, 1, 0, 1, -1, 0, -1, -1, 0, 1, 1, 0, 1, -1, 0, -1, 1, 0};
    static inline const std::vector<int> BACK = {1, 1, 0, -1, -1, 0, 1, -1, 0, -1, 1, 0, -1, -1, 0, 1, 1, 0};
    static inline const std::vector<int> LEFT = {
        0, 1, -1, 0, -1, 1, 0, -1, -1, 0, 1, 1, 0, -1, 1, 0, 1, -1,
    };
    static inline const std::vector<int> RIGHT = {
        -0, 1, 1, -0, -1, -1, -0, -1, 1, -0, 1, -1, -0, -1, -1, -0, 1, 1,
    };
    static inline const std::vector<int> UP = {
        -1, 0, 1, 1, 0, -1, -1, 0, -1, 1, 0, 1, 1, 0, -1, -1, 0, 1,
    };
    static inline const std::vector<int> DOWN = {
        -1, -0, -1, 1, -0, 1, -1, -0, 1, 1, -0, -1, 1, -0, 1, -1, -0, -1,
    };
};

inline void printVector(glm::vec3 vec)
{
    std::cout << "[INFO] | " << "X: " << vec.x << ", Y: " << vec.y << ", Z:" << vec.z;
}
