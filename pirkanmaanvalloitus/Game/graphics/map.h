
#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include "graphics/simplegamescene.h"
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "graphics/gamescene.h"
#include "graphics/mapitem.h"
#include "tiles/grassland.h"
#include "tiles/forest.h"
#include "tiles/tilebase.h"
#include "core/coordinate.h"
#include "tiles/stone.h"
#include "tiles/water.h"
#include "tiles/sand.h"
#include "graphics/simplemapitem.h"
#include <QPoint>
#include <vector>


namespace Student{
/*!
 * \brief The Map class initializes the game map using premade map .txt files, could be later updated to also save maps to allow saving and continuing the game
 */
class Map
{
public:
    Map(Student::GameScene* scene, std::string map_size, std::shared_ptr<Student::ObjectManager> objmanager, std::shared_ptr<Student::GameEventHandler> GEhandler);
    ~Map();
    /*
     * \brief InitializeMap initializes the map using information from settingwindow, and adds all made objects to objectmanager
     */
    void InitializeMap();


private:

    std::vector<Student::MapItem*> graphics_;
    std::vector<std::shared_ptr<TileBase>> tiles;
    Student::GameScene* scene_ = nullptr;
    std::string size_;
    std::shared_ptr<Student::ObjectManager> objmanager_ = nullptr;
    std::shared_ptr<Student::GameEventHandler> GEhandler_ = nullptr;
    std::shared_ptr<Course::PlayerBase> owner_ = nullptr;




};
}

#endif // MAP_H

