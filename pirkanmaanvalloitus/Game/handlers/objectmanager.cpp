#include "objectmanager.h"


namespace Student {


ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

QPoint ObjectManager::toIsometric(Course::Coordinate &point)
{
    int s_x = (point.asQpoint().rx() - point.asQpoint().ry())*32;
    int s_y = (point.asQpoint().rx() + point.asQpoint().ry())*16;
    return QPoint(s_x, s_y);
}



void ObjectManager::addTiles(const std::vector<std::shared_ptr<TileBase> > &tiles)
{
    for(auto it = tiles.begin(); it != tiles.end(); it++){
        tiles_.push_back(*it);
    }
}

void ObjectManager::addTileGraphics(const std::vector<MapItem*> &tile_graphics)
{
    for(auto it = tile_graphics.begin(); it != tile_graphics.end(); it++){
        graphics_.push_back(*it);
    }

}

void ObjectManager::addTile(std::shared_ptr<TileBase> &tile)
{
    tiles_.push_back(tile);
}

void ObjectManager::addGraphic(MapItem* item)
{
    graphics_.push_back(item);

}

void ObjectManager::addBuilding(std::shared_ptr<BuildingBase> &building)
{
    buildings_.push_back(building);
}


std::shared_ptr<TileBase> ObjectManager::getTile(const Coordinate &coordinate)
{
    for(auto it = tiles_.begin(); it != tiles_.end(); it++){
        std::shared_ptr<TileBase> tile = *it;
        if (tile->getCoordinate() == coordinate){
            return tile;
        }
    }
    return nullptr;
}


std::shared_ptr<TileBase> ObjectManager::getTile(const ObjectId &id)
{
    for(auto it = tiles_.begin(); it != tiles_.end(); it++){
        std::shared_ptr<TileBase> tile = *it;
        if(tile->ID == id){
            return tile;
        }
    }
    return nullptr;

}


std::vector<std::shared_ptr<TileBase> > ObjectManager::getTiles(const std::vector<Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<TileBase> > tiles;
    for(auto it = coordinates.begin(); it != coordinates.end(); it++){
        tiles.push_back(getTile(*it));
    }
    return tiles;

}

int ObjectManager::getProgress(std::shared_ptr<Course::PlayerBase> owner){
    int count = 0;
    int watercount =0;
    for(auto it = tiles_.begin(); it != tiles_.end(); it++){

        std::shared_ptr<TileBase> tile = *it;
        if(tile->getType() != "Water"){
            if(tile->getOwner() == owner){
                count++;
            }
        }else{
            watercount++;
        }
    }
    return 100*count/(tiles_.size()-watercount);
}

int ObjectManager::gatherResources(std::shared_ptr<Course::PlayerBase> owner, std::string type)
{
    int count = 0;
    for(auto it = tiles_.begin(); it != tiles_.end(); it++){
        std::shared_ptr<TileBase> tile = *it;
        if(tile->getType() == type && tile->getOwner() == owner){
            count +=1;
        }

    }
    return 5*count;
}

}
