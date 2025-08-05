#include "chunk_manager.hpp"
#include "chunk.hpp"

size_t ChunkManager::addChunk(Chunk chunk)
{
    this->chunks.push_back(chunk);
    return this->chunks.size() - 1;
}

void ChunkManager::freeChunk(size_t id)
{
    this->chunks.erase(chunks.begin() + id);
}
