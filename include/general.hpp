#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>

#define CODE_ERROR 1
#define CODE_NO_ERROR 0
#define CODE_FATAL_ERROR -1

const std::vector<int> FRONT = {-1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, 1, -1, -1, -1, 1, -1};
const std::vector<int> LEFT = {
    1, 1, -1, 1, -1, 1, 1, -1, -1, 1, 1, 1, 1, -1, 1, 1, 1, -1,
};
const std::vector<int> BACK = {1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, -1, -1, 1, 1, 1, 1};
const std::vector<int> RIGHT = {
    -1, 1, 1, -1, -1, -1, -1, -1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1,
};
const std::vector<int> UP = {
    -1, 1, 1, 1, 1, -1, -1, 1, -1, 1, 1, 1, 1, 1, -1, -1, 1, 1,
};
const std::vector<int> DOWN = {
    -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, -1, -1,
};

void printVector(glm::vec3 vec)
{
    std::cout << "[INFO] | " << "X: " << vec.x << ", Y: " << vec.y << ", Z:" << vec.z;
}
