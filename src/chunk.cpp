#include "chunk.hpp"
#include "block.hpp"
#include "general.hpp"
#include "shader.hpp"
#include "generation.hpp"

#include "tracy/Tracy.hpp"

#include <cstddef>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <utility>


Chunk::Chunk()
{
    this->genData();
    this->genRenderData();

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
}

Chunk::Chunk(glm::vec3 pos)
{
    this->position = pos;

    this->genData();
    this->genRenderData();

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
}

RESULT_CODE Chunk::setData(Block _data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE])
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

Block *Chunk::getData()
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
                Block thisBlock = this->getBlockAtR(positionR);
                positionR += this->position;

                if (thisBlock == BlockTypes::getBlockById(BLOCK::AIR))
                    continue;

                Block xBlock[2] = {this->getBlockAtNR(glm::vec3(positionR.x + 1, positionR.y, positionR.z)),
                                       this->getBlockAtNR(glm::vec3(positionR.x - 1, positionR.y, positionR.z))};
                Block yBlock[2] = {this->getBlockAtNR(glm::vec3(positionR.x, positionR.y + 1, positionR.z)),
                                       this->getBlockAtNR(glm::vec3(positionR.x, positionR.y - 1, positionR.z))};
                Block zBlock[2] = {this->getBlockAtNR(glm::vec3(positionR.x, positionR.y, positionR.z + 1)),
                                       this->getBlockAtNR(glm::vec3(positionR.x, positionR.y, positionR.z - 1))};

                std::vector<std::pair<Block, Direction>> a = {
                    {xBlock[1], getDirection(Directions::RIGHT)}, {xBlock[0], getDirection(Directions::LEFT)},
                    {yBlock[1], getDirection(Directions::DOWN)},  {yBlock[0], getDirection(Directions::UP)},
                    {zBlock[1], getDirection(Directions::FRONT)}, {zBlock[0], getDirection(Directions::BACK)}};

                for (size_t v = 0; v < a.size(); v++)
                {
                    if (a.at(v).first == BlockTypes::getBlockById(BLOCK::AIR))
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

Block Chunk::getBlockAtR(glm::vec3 pos)
{
    // INEFFICIENT
    if (pos.x < 0 or pos.x >= CHUNK_SIZE)
    {
        return generation::genBlockAt(pos);
    }

    if (pos.y < 0 or pos.y >= CHUNK_SIZE)
    {
        return generation::genBlockAt(pos);
    }

    if (pos.z < 0 or pos.z >= CHUNK_SIZE)
    {
        return generation::genBlockAt(pos);
    }

    return data[(int)pos.x + (int)pos.y * CHUNK_SIZE + (int)pos.z * CHUNK_SIZE * CHUNK_SIZE];
}

Block Chunk::getBlockAtNR(glm::vec3 pos)
{
    // INEFFICIENT
    if (pos.x < 0 + position.x or pos.x >= CHUNK_SIZE + position.x)
    {
        return generation::genBlockAt(pos);
    }

    if (pos.y < 0 + position.y or pos.y >= CHUNK_SIZE + position.y)
    {
        return generation::genBlockAt(pos);
    }

    if (pos.z < 0 + position.z or pos.z >= CHUNK_SIZE + position.z)
    {
        return generation::genBlockAt(pos);
    }

    glm::vec3 p = glm::vec3(pos.x - this->position.x, pos.y - this->position.y, pos.z - this->position.z);

    return data[(int)p.x + (int)p.y * CHUNK_SIZE + (int)p.z * CHUNK_SIZE * CHUNK_SIZE];
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
                    generation::genBlockAt(glm::vec3(k, j, i) + this->position);
            }
        }
    }

    return RESULT_CODE::CODE_NO_ERROR;
}

RESULT_CODE Chunk::draw()
{
    ZoneScoped;
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, 3, (void *)0);
    glBufferData(GL_ARRAY_BUFFER, this->renderData.size(), this->renderData.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, renderData.size());

    return RESULT_CODE::CODE_NO_ERROR;
}

