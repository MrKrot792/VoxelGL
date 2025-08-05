#include "block.hpp" 

Block BlockTypes::getBlockById(const BLOCK id)
{
    Block result = Block();
    switch (id)
    {
    case BLOCK::AIR:
        result = Block("Air", true);
        break;

    case BLOCK::DIRT:
        result = Block("Dirt");
        break;

    case BLOCK::GRASS:
        result = Block("Grass");
        break;

    case BLOCK::NO_BLOCK:
        result = Block();
        break;
    }
    return result;
}
