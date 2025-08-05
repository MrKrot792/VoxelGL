#pragma once

#include "shader.hpp"
#include "general.hpp"
#include "block.hpp"

#include <glm/fwd.hpp>

#include <vector>

#define CHUNK_SIZE 16

typedef std::vector<char> RenderData;

class Chunk
{
  private:
    Block data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    RenderData renderData;

    glm::vec3 position = {0, 0, 0};

    RESULT_CODE genRenderData();

    RESULT_CODE genData();

    GLuint VBO;

  public:
    Chunk();
    Chunk(glm::vec3 pos);

    RESULT_CODE setData(Block _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]);
    Block *getData();

    Block getBlockAtR(glm::vec3 pos);  // Position is relative to chunk
    Block getBlockAtNR(glm::vec3 pos); // Position is NOT relative to chunk

    RenderData getRenderData();

    RESULT_CODE draw();
};
