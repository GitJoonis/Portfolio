#include "map.h"
#include "mainwindow.hh"

namespace Student{




Map::Map(GameScene *scene, std::string map_size, std::shared_ptr<ObjectManager> objmanager, std::shared_ptr<GameEventHandler> GEhandler):
    scene_(scene),
    size_(map_size),
    objmanager_(objmanager),
    GEhandler_(GEhandler)


{

}

Map::~Map()
{

}

void Map::InitializeMap(){

    QString data;
    std::string data_std;
    QString fileName;
    int limit = 0;

    if(size_ == "Small"){
        fileName = ":/maps/maps/small.txt";
        scene_->resize(21, 21);
        limit = 21;
        Course::ResourceMap start_resources = {
        {BasicResource::MONEY, 1000},
        {BasicResource::FOOD, 1000},
        {BasicResource::WOOD, 1000},
        {BasicResource::STONE, 1000}
        };
        GEhandler_->modifyResources(owner_, start_resources);
    }
    else if(size_ == "Medium"){
        fileName = ":/maps/maps/medium.txt";
        scene_->resize(35, 35);
        limit = 35;
        Course::ResourceMap start_resources = {
        {BasicResource::MONEY, 1000},
        {BasicResource::FOOD, 1000},
        {BasicResource::WOOD, 1000},
        {BasicResource::STONE, 1000}
        };
        GEhandler_->modifyResources(owner_, start_resources);
    }


    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Cant open file" << endl;
    }
    else
    {
        data = file.readAll();
    }
    data_std = data.toStdString();
    data_std.erase(std::remove(data_std.begin(), data_std.end(), '\n'), data_std.end());
    data_std.erase(std::remove(data_std.begin(), data_std.end(), '\r'), data_std.end());

    int x = 0;
    int y = 0;


    for(char& ch : data_std){

        if(x >= limit){
            y++;
            x = 0;
        }

        auto coord = Coordinate(x,y);

        if(ch==' '){
            break;
        }

        else if (ch=='g'){
            tiles.push_back(std::make_shared<Course::Grassland>(coord, GEhandler_, objmanager_));
            graphics_.push_back(new Student::MapItem(tiles.back(), 64, 32));

        }
        else if (ch=='w'){
            tiles.push_back(std::make_shared<Student::Water>(coord, GEhandler_, objmanager_));
            graphics_.push_back(new Student::MapItem(tiles.back(), 64, 32));

        }
        else if (ch=='s'){
            tiles.push_back(std::make_shared<Student::Stone>(coord, GEhandler_, objmanager_));
            graphics_.push_back(new Student::MapItem(tiles.back(), 64, 32));

        }
        else if (ch=='f'){            
            tiles.push_back(std::make_shared<Course::Forest>(coord, GEhandler_, objmanager_));
            graphics_.push_back(new Student::MapItem(tiles.back(), 64, 32));
        }
        else if (ch=='b'){
            tiles.push_back(std::make_shared<Student::Sand>(coord, GEhandler_, objmanager_));
            graphics_.push_back(new Student::MapItem(tiles.back(), 64, 32));
        }

        scene_->addItem(graphics_.back());
        x++;

    }   
    objmanager_->addTiles(tiles);
    objmanager_->addTileGraphics(graphics_);
}



} //namespace

