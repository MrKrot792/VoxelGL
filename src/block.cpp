#include "block.hpp" 

std::unordered_map<size_t, Block> BlockTypes::blocksById{};
std::unordered_map<std::string, Block> BlockTypes::blocksByName{};
size_t BlockTypes::nextId = 0;
