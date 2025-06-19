#pragma once

#include "glad/glad.h"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

// std
#include <string>

class Shader
{
  public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setMatrix4(const std::string &name, const glm::mat4 &value) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;
};
