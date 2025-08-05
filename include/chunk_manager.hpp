#pragma once

#include "chunk.hpp"
#include "glm/fwd.hpp"

#include <vector>

#include <cstddef>

// Basically a singleton
class ChunkManager
{
  private:
    ChunkManager() = default;
    ~ChunkManager() = default;

  public:
    static ChunkManager &getInstance()
    {
        static ChunkManager instance;
        return instance;
    }

    ChunkManager(const ChunkManager &) = delete;
    ChunkManager &operator=(const ChunkManager &) = delete;
    ChunkManager(ChunkManager &&) = delete;
    ChunkManager &operator=(ChunkManager &&) = delete;

    // Returns the ID of placed chunk.
    size_t addChunk(Chunk chunk);

    // Takes the ID of the chunk
    void freeChunk(size_t id);

    Block getBlockAt(glm::vec3 pos);
    void setBlockAt(Block block);

    std::vector<Chunk> chunks{};
};
