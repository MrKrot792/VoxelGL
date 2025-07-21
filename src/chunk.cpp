#include "chunk.hpp"
#include "general.hpp"
#include "shader.hpp"

#include <cstddef>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <iostream>
#include <utility>

Chunk::Chunk()
{
    srand(time(0));
    this->genData();
    this->genRenderData();

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
}

Chunk::Chunk(glm::vec3 pos)
{
    this->position = pos;

    srand(time(0));
    this->genData();
    this->genRenderData();

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
}

RESULT_CODE Chunk::setData(BlockData _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE])
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

    return RESULT_CODE::CODE_NO_ERROR;
}

BlockData *Chunk::getData()
{
    return this->data;
}

RESULT_CODE Chunk::genRenderData()
{
    this->renderData.clear();

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                glm::vec3 positionR(k, j, i);
                BlockData thisBlock = this->getBlockAtR(positionR);
                positionR += this->position;

                if (thisBlock.type == AIR)
                    continue;

                BlockData xBlock[2] = {this->getBlockAtR(glm::vec3(k + 1, j, i)),
                                       this->getBlockAtR(glm::vec3(k - 1, j, i))};
                BlockData yBlock[2] = {this->getBlockAtR(glm::vec3(k, j + 1, i)),
                                       this->getBlockAtR(glm::vec3(k, j - 1, i))};
                BlockData zBlock[2] = {this->getBlockAtR(glm::vec3(k, j, i + 1)),
                                       this->getBlockAtR(glm::vec3(k, j, i - 1))};

                if (xBlock[0].type != AIR && xBlock[1].type != AIR && yBlock[0].type != AIR && yBlock[1].type != AIR &&
                    zBlock[0].type != AIR && zBlock[1].type != AIR)
                {
                    continue;
                }

                std::vector<std::pair<BlockData, Direction>> a = {
                    {xBlock[1], getDirection(Directions::RIGHT)}, {xBlock[0], getDirection(Directions::LEFT)},
                    {yBlock[1], getDirection(Directions::DOWN)},  {yBlock[0], getDirection(Directions::UP)},
                    {zBlock[1], getDirection(Directions::FRONT)}, {zBlock[0], getDirection(Directions::BACK)}};

                for (size_t v = 0; v < a.size(); v++)
                {
                    if (a.at(v).first.type == AIR)
                    {
                        for (size_t n = 0; n < a.at(v).second.size() / 3; n++)
                        {
                            this->renderData.push_back(a.at(v).second.at(n * 3 + 0) + positionR.x);
                            this->renderData.push_back(a.at(v).second.at(n * 3 + 1) + positionR.y);
                            this->renderData.push_back(a.at(v).second.at(n * 3 + 2) + positionR.z);
                        }
                    }
                }
            }
        }
    }

    return RESULT_CODE::CODE_NO_ERROR;
}

RenderData Chunk::getRenderData()
{
    this->genRenderData();
    return this->renderData;
}

BlockData Chunk::getBlockAtR(glm::vec3 pos)
{
    if (pos.x < 0 or pos.x >= CHUNK_SIZE)
    {
        return BlockData(AIR);
    }

    if (pos.y < 0 or pos.y >= CHUNK_SIZE)
    {
        return BlockData(AIR);
    }

    if (pos.z < 0 or pos.z >= CHUNK_SIZE)
    {
        return BlockData(AIR);
    }

    return data[(int)pos.x + (int)pos.y * CHUNK_SIZE + (int)pos.z * CHUNK_SIZE * CHUNK_SIZE];
}

BlockData Chunk::getBlockAtNR(glm::vec3 pos)
{
    if (pos.x < 0 + position.x or pos.x >= CHUNK_SIZE + position.x)
    {
        return BlockData(AIR);
    }

    if (pos.y < 0 + position.y or pos.y >= CHUNK_SIZE + position.y)
    {
        return BlockData(AIR);
    }

    if (pos.z < 0 + position.z or pos.z >= CHUNK_SIZE + position.z)
    {
        return BlockData(AIR);
    }

    return data[(int)pos.x + (int)pos.y * CHUNK_SIZE + (int)pos.z * CHUNK_SIZE * CHUNK_SIZE];
}

RESULT_CODE Chunk::genData()
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] =
                    this->genBlockAt(glm::vec3(k, j, i) + this->position);
            }
        }
    }

    return RESULT_CODE::CODE_NO_ERROR;
}

BlockData Chunk::genBlockAt(glm::vec3 pos)
{
    BLOCK_TYPE result = DIRT;

    // Procedural generation (kinda)

    if (pos == glm::vec3(5, 5, 9))
        result = AIR;

    if (pos == glm::vec3(7, 5, 9))
        result = AIR;

    if (pos == glm::vec3(5, 5, 13))
        result = AIR;

    if (pos == glm::vec3(6, 5, 13))
        result = AIR;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                if (pos == glm::vec3(i + 3, j + 3, k + 3))
                    result = AIR;
            }
        }
    }

    return BlockData(result);
}

RESULT_CODE Chunk::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, 3, (void *)0);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, renderData.size());

    return RESULT_CODE::CODE_NO_ERROR;
}
