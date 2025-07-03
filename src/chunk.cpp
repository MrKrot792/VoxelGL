#include "chunk.hpp"
#include "general.hpp"
#include "shader.hpp"

#include <cstdlib>
#include <glm/fwd.hpp>

// std
#include <iostream>
#include <utility>

Chunk::Chunk()
{
    // Placehorder for a generator

    srand(time(0));

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                // int x = i * 2 - CHUNK_SIZE;
                // int y = j * 2 - CHUNK_SIZE;
                // int z = k * 2 - CHUNK_SIZE;
                this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] = AIR;

                if (k > CHUNK_SIZE / 2)
                {
                    this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] = DIRT;
                }

                // if (std::rand() < RAND_MAX / 10.f)
                //     this->data[k + j * CHUNK_SIZE + i * CHUNK_SIZE * CHUNK_SIZE] = DIRT;
            }
        }
    }

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
                auto position = glm::vec3(k, j, i);
                BLOCK thisBlock = this->getBlockAtR(position);

                // Surrounding blocks
                BLOCK xBlock[2] = {this->getBlockAtR(glm::vec3(k + 1, j, i)),
                                   this->getBlockAtR(glm::vec3(k - 1, j, i))};
                BLOCK yBlock[2] = {this->getBlockAtR(glm::vec3(k, j + 1, i)),
                                   this->getBlockAtR(glm::vec3(k, j - 1, i))};
                BLOCK zBlock[2] = {this->getBlockAtR(glm::vec3(k, j, i + 1)),
                                   this->getBlockAtR(glm::vec3(k, j, i - 1))};

                if (xBlock[0] != AIR and xBlock[1] != AIR)
                {
                    if (yBlock[0] != AIR and yBlock[1] != AIR)
                    {
                        if (zBlock[0] != AIR and zBlock[1] != AIR)
                        {
                            std::cout << "Avoiding block at ";
                            printVector(position);
                            std::cout << std::endl;
                        }
                    }
                }

                if (thisBlock == AIR)
                    continue;

                std::pair<glm::vec3, BLOCK> pair = std::pair(glm::vec3(k, j, i), thisBlock);

                this->renderData.push_back(pair);
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
