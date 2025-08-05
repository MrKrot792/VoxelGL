#pragma once

// TODO: Add a support for yaml

#include <iostream>
#include <string>
#include <unordered_map>

#include <bits/monostate.h>
#include <cstddef>

enum class BLOCK
{
    AIR,
    DIRT,
    GRASS,
    NO_BLOCK,
};

class Block
{
  public:
    std::string name; // Very extendable
    bool isTransparent = false;

    Block(const std::string &name) : name(name)
    {
    }

    // Very unsafe, and is NOT what i wanted to do, but i have no options
    Block() : name("Air")
    {
    }

    bool operator==(Block o)
    {
        return this->name == o.name;
    }
};

class BlockTypes
{
  private:
    BlockTypes();
    ~BlockTypes() = default;

    static std::unordered_map<size_t, Block> blocksById;
    static std::unordered_map<std::string, Block> blocksByName;

    static size_t nextId;

  public:
    BlockTypes(const BlockTypes &) = delete;
    BlockTypes &operator=(const BlockTypes &) = delete;
    BlockTypes(BlockTypes &&) = delete;
    BlockTypes &operator=(BlockTypes &&) = delete;

    static void initialize()
    {
        // Adding blocks to list
        std::cout << BlockTypes::registerBlock("Air") << "\n";
        std::cout << BlockTypes::registerBlock("Dirt") << "\n";
        std::cout << BlockTypes::registerBlock("Grass") << "\n";
        std::cout << BlockTypes::registerBlock("NO_BLOCK") << "\n";
    }

    static int registerBlock(const std::string &name)
    {
        size_t id = nextId++;
        auto b = Block(name);
        blocksById.emplace(id, b);
        blocksByName.emplace(name, b);
        return id;
    }

    static int registerBlock()
    {
        size_t id = nextId++;
        blocksById.emplace(id, Block());
        blocksByName.emplace("Air", Block());
        return id;
    }

    static Block getBlockById(const size_t id)
    {
        auto it = blocksById.find(id);

        if(it == blocksById.end())
        {
            std::cerr << "[ERROR] | Block ID not found: " << id << std::endl;
            std::terminate();
        }

        return it->second;
    }

    static Block getBlockByName(const std::string &name)
    {
        auto it = blocksByName.find(name);
        if (it == blocksByName.end())
        {
            std::cerr << "[ERROR] | Block name not found: " << name << std::endl;
            std::terminate();
        }
        return it->second;
    }
};
