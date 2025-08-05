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

    Block(const std::string &name, bool isTransparent) : name(name), isTransparent(isTransparent)
    {
    }
    // Very unsafe, and is NOT what i wanted to do, but i have no options
    Block() : name("NO_BLOCK"), isTransparent(true)
    {
    }

    bool operator==(Block o)
    {
        return (this->name == o.name) && (this->isTransparent == o.isTransparent);
    }
};

class BlockTypes
{
  private:
    BlockTypes();
    ~BlockTypes() = default;

  public:
    BlockTypes(const BlockTypes &) = delete;
    BlockTypes &operator=(const BlockTypes &) = delete;
    BlockTypes(BlockTypes &&) = delete;
    BlockTypes &operator=(BlockTypes &&) = delete;

    static Block getBlockById(const BLOCK id);
};
