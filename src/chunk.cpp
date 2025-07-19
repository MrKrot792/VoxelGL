#include "chunk.hpp"
#include "general.hpp"
#include "shader.hpp"

#include <cstddef>
#include <cstdlib>
#include <glm/fwd.hpp>

Chunk::Chunk()
{
    srand(time(0));

    this->genData();

    this->chunk_shader = Shader("shaders/vertex.vert", "shaders/fragment.frag");
}

RESULT_CODE Chunk::setData(BLOCK _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE])
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

BLOCK *Chunk::getData()
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
                glm::vec3 position(k, j, i);
                BLOCK thisBlock = this->getBlockAtR(position);
                position += this->position;

                if (thisBlock == AIR)
                    continue;

                BLOCK xBlock[2] = {this->getBlockAtR(glm::vec3(k + 1, j, i)),
                                   this->getBlockAtR(glm::vec3(k - 1, j, i))};
                BLOCK yBlock[2] = {this->getBlockAtR(glm::vec3(k, j + 1, i)),
                                   this->getBlockAtR(glm::vec3(k, j - 1, i))};
                BLOCK zBlock[2] = {this->getBlockAtR(glm::vec3(k, j, i + 1)),
                                   this->getBlockAtR(glm::vec3(k, j, i - 1))};

                if (xBlock[0] != AIR && xBlock[1] != AIR && yBlock[0] != AIR && yBlock[1] != AIR && zBlock[0] != AIR &&
                    zBlock[1] != AIR)
                {
                    continue;
                }

                // I know this is very highly unoptimized shit, please don't execute me
                if (xBlock[1] == AIR)
                {
                    for (size_t i = 0; i < Directions::RIGHT.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::RIGHT.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::RIGHT.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::RIGHT.at(i * 3 + 2) + position.z);
                    }
                }

                if (xBlock[0] == AIR)
                {
                    for (size_t i = 0; i < Directions::LEFT.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::LEFT.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::LEFT.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::LEFT.at(i * 3 + 2) + position.z);
                    }
                }

                if (yBlock[1] == AIR)
                {
                    for (size_t i = 0; i < Directions::DOWN.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::DOWN.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::DOWN.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::DOWN.at(i * 3 + 2) + position.z);
                    }
                }

                if (yBlock[0] == AIR)
                {
                    for (size_t i = 0; i < Directions::UP.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::UP.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::UP.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::UP.at(i * 3 + 2) + position.z);
                    }
                }

                if (zBlock[1] == AIR)
                {
                    for (size_t i = 0; i < Directions::FRONT.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::FRONT.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::FRONT.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::FRONT.at(i * 3 + 2) + position.z);
                    }
                }

                if (zBlock[0] == AIR)
                {
                    for (size_t i = 0; i < Directions::BACK.size() / 3; i++)
                    {
                        this->renderData.push_back(Directions::BACK.at(i * 3 + 0) + position.x);
                        this->renderData.push_back(Directions::BACK.at(i * 3 + 1) + position.y);
                        this->renderData.push_back(Directions::BACK.at(i * 3 + 2) + position.z);
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

BLOCK Chunk::getBlockAtR(glm::vec3 pos)
{
    if (pos.x < 0 or pos.x >= CHUNK_SIZE)
    {
        return AIR;
    }

    if (pos.y < 0 or pos.y >= CHUNK_SIZE)
    {
        return AIR;
    }

    if (pos.z < 0 or pos.z >= CHUNK_SIZE)
    {
        return AIR;
    }

    return data[(int)pos.x + (int)pos.y * CHUNK_SIZE + (int)pos.z * CHUNK_SIZE * CHUNK_SIZE];
}

BLOCK Chunk::getBlockAtNR(glm::vec3 pos)
{
    return AIR;
}

RESULT_CODE Chunk::genData()
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

    return RESULT_CODE::CODE_NO_ERROR;
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
