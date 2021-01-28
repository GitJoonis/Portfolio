#ifndef RESOURCES_H
#define RESOURCES_H
#include "core/resourcemaps.h"

namespace Student {

namespace ConstResourceMaps {
//this header is used to store different resourcemaps

const Course::ResourceMap EMPTY = {};

// Building - Farm
const Course::ResourceMap FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, -50},
    {Course::BasicResource::FOOD, 0 },
    {Course::BasicResource::WOOD, -50}
};


// Building - HeadQuarters
const Course::ResourceMap HQ_BUILD_COST = {
    {Course::BasicResource::MONEY, -500},
    {Course::BasicResource::FOOD, -100},
    {Course::BasicResource::WOOD, -500},
    {Course::BasicResource::STONE, -500}
};


const Course::ResourceMap HOUSE_BUILD_COST = {
    {Course::BasicResource::STONE, -50},
    {Course::BasicResource::WOOD, -50},
    };

const Course::ResourceMap MARKET_BUILD_COST = {
    {Course::BasicResource::FOOD, -50},
    {Course::BasicResource::WOOD, -50},
    {Course::BasicResource::STONE, -50},
    };

const Course::ResourceMap BRIDGE_BUILD_COST = {
    {Course::BasicResource::WOOD, 20},
    };

const Course::ResourceMap PASSIVE_COST = {
  {Course::BasicResource::FOOD, -20},
};

const Course::ResourceMap SELL_RESOURCES_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, -50},
    {Course::BasicResource::STONE, -50}
};

const Course::ResourceMap BUY_RESOURCES_COST = {
    {Course::BasicResource::MONEY, -50},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 50},
    {Course::BasicResource::STONE, 50}
};



}
}

#endif // RESOURCES_H
