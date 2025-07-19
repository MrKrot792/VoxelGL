#pragma once

#include "shader.hpp"
#include <glm/fwd.hpp>
#include <utility>
#include <vector>

#include "general.hpp"

#define CHUNK_SIZE 16

enum BLOCK
{
    NO_BLOCK,
    AIR,
    DIRT,
    GRASS,
};

typedef std::pair<glm::vec3, BLOCK> BlockData;
typedef std::vector<char> RenderData;

class Chunk
{
  private:
    BLOCK data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    RenderData renderData;

    glm::vec3 position; // Chunk position in the world divided by CHUNK_SIZE

    RESULT_CODE genRenderData();

    RESULT_CODE genData();
    BLOCK genBlockAt(int x, int y, int z);

    GLuint VBO;

  public:
    Chunk();

    RESULT_CODE setData(BLOCK _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]);
    BLOCK *getData();

    BLOCK getBlockAtR(glm::vec3 pos); // Position is relative to chunk
    BLOCK getBlockAtNR(glm::vec3 pos); // Position is NOT relative to chunk

    RenderData getRenderData();

    RESULT_CODE draw();
};
