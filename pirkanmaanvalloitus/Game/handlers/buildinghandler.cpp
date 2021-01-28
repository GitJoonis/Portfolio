#include "buildinghandler.h"

namespace Student{

BuildingHandler::BuildingHandler(GameScene *scene, std::shared_ptr<Student::ObjectManager> objmanager, std::shared_ptr<Student::GameEventHandler> GEhandler)
{
    scene_ = scene;
    objmanager_ = objmanager;
    GEhandler_ = GEhandler;

}

BuildingHandler::~BuildingHandler()
{

}



bool BuildingHandler::addHouse(QPoint pos, QPoint coord_, std::shared_ptr<Course::PlayerBase> owner_)
{

    auto tiles = scene_->items(pos);
    //if something is highlighted and the tile is of type Student::MapItem
    if(tiles[1]->type() == MapitemID){
        if(static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Grassland" && static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Sand"){
            std::string msg = "You can only make Houses on grassland or sand";
            scene_->emitMessage(msg);
            return 0;
        }
        else if (static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getOwner() == owner_){

            if(!GEhandler_->compareResources(Student::ConstResourceMaps::HOUSE_BUILD_COST)){
                std::string msg = "Not enough resources";
                scene_->emitMessage(msg);
                return 0;
            }

            // tile is Grass, make a house
            GEhandler_->modifyResources(owner_, Student::ConstResourceMaps::HOUSE_BUILD_COST);
            std::shared_ptr<Course::BuildingBase> building = std::make_shared<Student::House>(GEhandler_, objmanager_, owner_);
            building->setCoordinate(Course::Coordinate(coord_.x(), coord_.y()));
            Student::MapItem* buildingGraphic = new Student::MapItem(building, 64, 32);

            //store building
            objmanager_->addBuilding(building);
            objmanager_->addGraphic(buildingGraphic);

            //add building as a child for the tile
            buildingGraphic->setParentItem(tiles[1]);
            captureLand(coord_, 5, owner_);
            return 1;
        }
        else{
            std::string msg = "You do not own this tile.";
            scene_->emitMessage(msg);
            return 0;
        }

    }
    return 0;

}

bool BuildingHandler::deleteBuilding(QPoint pos)
{

    auto tiles = scene_->items(pos);
    //if tiles is Student::MapItem
    if(tiles[1]->type() == MapitemID){

        QList<QGraphicsItem* >::iterator i;
        for (i = tiles.begin(); i != tiles.end(); i++){
            if(!(*i)->childItems().empty()){
                scene_->removeItem((*i)->childItems().back());
                return 1;
            }
        }
    }
    return 0;

}

void BuildingHandler::captureLand(QPoint coord, int size, std::shared_ptr<Course::PlayerBase> owner_)
{
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            Course::Coordinate coordinate = Course::Coordinate(coord.x()-floor(size/2)+x,coord.y()-floor(size/2)+y);
            if(objmanager_->getTile(coordinate) != nullptr){
                objmanager_->getTile(coordinate)->setOwner(owner_);
            }
        }
    }
}


bool BuildingHandler::addHQ(QPoint pos, QPoint coord_, std::shared_ptr<Course::PlayerBase> owner_)
{

    auto tiles = scene_->items(pos);
    //if something is highlighted and the tile is of type Student::MapItem
    if(tiles[1]->type() == MapitemID){
        if(static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Grassland"){
            std::string msg = "You can only make Headquarters on grassland";
            scene_->emitMessage(msg);
            return 0;
        }
        else if (static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getOwner() == owner_ || objmanager_->getProgress(owner_)==0){
            if(!GEhandler_->compareResources(Student::ConstResourceMaps::HQ_BUILD_COST)){
                std::string msg = "Not enough resources";
                scene_->emitMessage(msg);
                return 0;
            }
            // tile is Grass, make HQ
            GEhandler_->modifyResources(owner_, Student::ConstResourceMaps::HQ_BUILD_COST);
            std::shared_ptr<Course::BuildingBase> building = std::make_shared<Course::HeadQuarters>(GEhandler_, objmanager_, owner_);
            building->setCoordinate(Course::Coordinate(coord_.x(), coord_.y()));
            Student::MapItem* buildingGraphic = new Student::MapItem(building, 64, 32);

            //store building
            objmanager_->addBuilding(building);
            objmanager_->addGraphic(buildingGraphic);

            //add building as a child for the tile
            buildingGraphic->setParentItem(tiles[1]);
            static_cast<Student::MapItem*>(tiles[1])->getGameObject()->setOwner(owner_);
            captureLand(coord_, 7, owner_);
            return 1;

        }
        else{
            std::string msg = "You do not own this tile";
            scene_->emitMessage(msg);
            return 0;
        }
    }
    return 0;
}

bool BuildingHandler::addBridge(QPoint pos, QPoint coord_, std::shared_ptr<Course::PlayerBase> owner_)
{

    auto tiles = scene_->items(pos);
    //if something is highlighted and the tile is of type Student::MapItem
    if(tiles[1]->type() == MapitemID){
        if(static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Water"){
            std::string msg = "You can only make Bridges on water";
            scene_->emitMessage(msg);
            return 0;
        }
        else if (static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getOwner() == owner_){

            if(!GEhandler_->compareResources(Student::ConstResourceMaps::BRIDGE_BUILD_COST)){
                std::string msg = "Not enough resources";
                scene_->emitMessage(msg);
                return 0;
            }

            // tile is Water, make bridge
            GEhandler_->modifyResources(owner_, Student::ConstResourceMaps::BRIDGE_BUILD_COST);
            std::shared_ptr<Course::BuildingBase> building = std::make_shared<Student::Bridge>(GEhandler_, objmanager_, owner_);
            building->setCoordinate(Course::Coordinate(coord_.x(), coord_.y()));
            Student::MapItem* buildingGraphic = new Student::MapItem(building, 64, 32);

            //store building
            objmanager_->addBuilding(building);
            objmanager_->addGraphic(buildingGraphic);

            //add building as a child for the tile
            buildingGraphic->setParentItem(tiles[1]);
            captureLand(coord_, 3, owner_);
            return 1;

        }
        else{
            std::string msg = "You do not own this tile";
            scene_->emitMessage(msg);
            return 0;
        }
    }
    return 0;


}

bool BuildingHandler::addMarket(QPoint pos, QPoint coord_, std::shared_ptr<Course::PlayerBase> owner_)
{
    auto tiles = scene_->items(pos);
    //if something is highlighted and the tile is of type Student::MapItem
    if(tiles[1]->type() == MapitemID){
        if(static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Sand"){
            std::string msg = "You can only make Markets on sand";
            scene_->emitMessage(msg);
            return 0;
        }
        else if (static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getOwner() == owner_){

            if(!GEhandler_->compareResources(Student::ConstResourceMaps::MARKET_BUILD_COST)){
                std::string msg = "Not enough resources";
                scene_->emitMessage(msg);
                return 0;
            }

            // tile is Sand, make Market
            GEhandler_->modifyResources(owner_, Student::ConstResourceMaps::MARKET_BUILD_COST);
            std::shared_ptr<Course::BuildingBase> building = std::make_shared<Student::Market>(GEhandler_, objmanager_, owner_);
            building->setCoordinate(Course::Coordinate(coord_.x(), coord_.y()));
            Student::MapItem* buildingGraphic = new Student::MapItem(building, 64, 32);

            //store building
            objmanager_->addBuilding(building);
            objmanager_->addGraphic(buildingGraphic);

            //add building as a child for the tile
            buildingGraphic->setParentItem(tiles[1]);
            captureLand(coord_, 5, owner_);
            return 1;

        }
        else{
            std::string msg = "You do not own this tile";
            scene_->emitMessage(msg);
            return 0;
        }
    }
    return 0;

}

bool BuildingHandler::addFarm(QPoint pos, QPoint coord_, std::shared_ptr<Course::PlayerBase> owner_)
{
    auto tiles = scene_->items(pos);
    //if something is highlighted and the tile is of type Student::MapItem
    if(tiles[1]->type() == MapitemID){
        if(static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getType() != "Grassland"){
            std::string msg = "You can only make Farms on Grassland";
            scene_->emitMessage(msg);
            return 0;
        }
        else if (static_cast<Student::MapItem*>(tiles[1])->getGameObject()->getOwner() == owner_){

            if(!GEhandler_->compareResources(Student::ConstResourceMaps::FARM_BUILD_COST)){
                std::string msg = "Not enough resources";
                scene_->emitMessage(msg);
                return 0;
            }

            // tile is grass, make farm
            GEhandler_->modifyResource(owner_, Course::FOOD, 100);
            GEhandler_->modifyResources(owner_, Student::ConstResourceMaps::FARM_BUILD_COST);
            std::shared_ptr<Course::BuildingBase> building = std::make_shared<Student::Farm>(GEhandler_, objmanager_, owner_);
            building->setCoordinate(Course::Coordinate(coord_.x(), coord_.y()));
            Student::MapItem* buildingGraphic = new Student::MapItem(building, 64, 32);

            //store building
            objmanager_->addBuilding(building);
            objmanager_->addGraphic(buildingGraphic);

            //add building as a child for the tile
            buildingGraphic->setParentItem(tiles[1]);

            return 1;

        }
        else{
            std::string msg = "You do not own this tile";
            scene_->emitMessage(msg);
            return 0;
        }
    }

    return 0;

}

}
