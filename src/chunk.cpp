#include "chunk.hpp"
#include "general.hpp"
#include "shader.hpp"

#include <cstdlib>
#include <glm/fwd.hpp>

Chunk::Chunk()
{
    srand(time(0));

    this->genData();

    this->chunk_shader = Shader("shaders/vertex.vert", "shaders/fragment.frag");
}

int Chunk::setData(BLOCK _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE])
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] =
                    _data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE];
            }
        }
    }

    return CODE_NO_ERROR;
}

BLOCK *Chunk::getData()
{
    return this->data;
}

int Chunk::genRenderData()
{
    this->renderData.clear();

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                glm::vec3 position(k, j, i);
                BLOCK thisBlock = this->getBlockAtR(position);

                if (thisBlock == AIR)
                    continue;

                BLOCK xBlock[2] = {(k + 1 < CHUNK_SIZE ? this->getBlockAtR(glm::vec3(k + 1, j, i)) : AIR),
                                   (k - 1 >= 0 ? this->getBlockAtR(glm::vec3(k - 1, j, i)) : AIR)};
                BLOCK yBlock[2] = {(j + 1 < CHUNK_SIZE ? this->getBlockAtR(glm::vec3(k, j + 1, i)) : AIR),
                                   (j - 1 >= 0 ? this->getBlockAtR(glm::vec3(k, j - 1, i)) : AIR)};
                BLOCK zBlock[2] = {(i + 1 < CHUNK_SIZE ? this->getBlockAtR(glm::vec3(k, j, i + 1)) : AIR),
                                   (i - 1 >= 0 ? this->getBlockAtR(glm::vec3(k, j, i - 1)) : AIR)};

                if (xBlock[0] != AIR && xBlock[1] != AIR && yBlock[0] != AIR && yBlock[1] != AIR && zBlock[0] != AIR &&
                    zBlock[1] != AIR)
                {
                    continue;
                }

                this->renderData.emplace_back(position, thisBlock);
            }
        }
    }

    return CODE_NO_ERROR;
}

RenderData Chunk::getRenderData()
{
    this->genRenderData();
    return this->renderData;
}

BLOCK Chunk::getBlockAtR(glm::vec3 pos)
{
    if (pos.x < 0 || pos.x >= CHUNK_SIZE)
    {
        if (pos.y < 0 || pos.y >= CHUNK_SIZE)
        {
            if (pos.z < 0 || pos.z >= CHUNK_SIZE)
            {
                return NO_BLOCK;
            }
        }
    }

    return data[(int)pos.x + (int)pos.y * CHUNK_SIZE + (int)pos.z * CHUNK_SIZE * CHUNK_SIZE];
}

BLOCK Chunk::getBlockAtNR(glm::vec3 pos)
{
    return NO_BLOCK;
}

int Chunk::genData()
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] = this->genBlockAt(i, j, k);
            }
        }
    }

    return CODE_NO_ERROR;
}

BLOCK Chunk::genBlockAt(int x, int y, int z)
{
    BLOCK result = AIR;

    if (y < 10)
    {
        result = DIRT;
    }

    if (x < 10)
    {
        result = DIRT;
    }

    if (z < 10)
    {
        result = DIRT;
    }

    return result;
}
