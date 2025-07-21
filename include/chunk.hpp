#pragma once

#include "shader.hpp"
#include <glm/fwd.hpp>
#include <vector>

#include "general.hpp"

#define CHUNK_SIZE 16

enum BLOCK_TYPE
{
    AIR,
    DIRT,
    GRASS,
    NO_BLOCK = 255,
};

typedef struct BlockData
{
    BLOCK_TYPE type = AIR;

    BlockData() = default;
    BlockData(BLOCK_TYPE t)
    {
        type = t;
    };

} BlockData_t;

typedef std::vector<char> RenderData;

class Chunk
{
  private:
    BlockData data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    RenderData renderData;

    glm::vec3 position = {0, 0, 0};

    RESULT_CODE genRenderData();

    RESULT_CODE genData();
    BlockData genBlockAt(glm::vec3 pos);

    GLuint VBO;

  public:
    Chunk();
    Chunk(glm::vec3 pos);

    RESULT_CODE setData(BlockData _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]);
    BlockData *getData();

    BlockData getBlockAtR(glm::vec3 pos);  // Position is relative to chunk
    BlockData getBlockAtNR(glm::vec3 pos); // Position is NOT relative to chunk

    RenderData getRenderData();

    RESULT_CODE draw();
};
