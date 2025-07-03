#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <iostream>

#define CODE_ERROR 1
#define CODE_NO_ERROR 0
#define CODE_FATAL_ERROR -1

void printVector(glm::vec3 vec)
{
    std::cout << "X: " << vec.x << ", Y: " << vec.y << ", Z:" << vec.z; 
}
