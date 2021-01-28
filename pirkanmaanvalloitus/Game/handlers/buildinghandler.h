#ifndef BUILDINGHANDLER_H
#define BUILDINGHANDLER_H
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "graphics/gamescene.h"
#include "buildings/house.h"
#include "buildings/headquarters.h"
#include "buildings/bridge.h"
#include "buildings/market.h"
#include "buildings/farm.h"
#include "buildings/farm.h"
#include "tiles/grassland.h"
#include "resources.h"
#include <QtCore>

namespace Student{
/*
 * \brief The BuildingHandler class is used to add buildings into the graphicsscene, and handle the consequences in objmanager and GEhandler
 */
class BuildingHandler:public QObject
{
    Q_OBJECT
public:
    BuildingHandler(Student::GameScene* scene, std::shared_ptr<Student::ObjectManager> objmanager, std::shared_ptr<Student::GameEventHandler> GEhandler);

    /*
     * \brief addHQ adds a headquarters building to the scene
     * \param pos position where the building is added
     * \param coord position in isometric coordinates
     * \param owner_ owner of the building
     * \return truth value whether add was succesful or not
     */
    bool addHQ(QPoint pos, QPoint coord, std::shared_ptr<Course::PlayerBase> owner_);

    /*
     * \brief addHouse adds a headquarters building to the scene
     * \param pos position where the building is added
     * \param coord position in isometric coordinates
     * \param owner_ owner of the building
     * \return truth value whether add was succesful or not
     */
    bool addHouse(QPoint pos, QPoint coord, std::shared_ptr<Course::PlayerBase> owner_);

    /*
     * \brief addBridge adds a headquarters building to the scene
     * \param pos position where the building is added
     * \param coord position in isometric coordinates
     * \param owner_ owner of the building
     * \return truth value whether add was succesful or not
     */
    bool addBridge(QPoint pos, QPoint coord, std::shared_ptr<Course::PlayerBase> owner_);

    /*
     * \brief addMarket adds a headquarters building to the scene
     * \param pos position where the building is added
     * \param coord position in isometric coordinates
     * \param owner_ owner of the building
     * \return truth value whether add was succesful or not
     */
    bool addMarket(QPoint pos, QPoint coord, std::shared_ptr<Course::PlayerBase> owner_);

    /*
     * \brief addFarm adds a headquarters building to the scene
     * \param pos position where the building is added
     * \param coord position in isometric coordinates
     * \param owner_ owner of the building
     * \return truth value whether add was succesful or not
     */
    bool addFarm(QPoint pos, QPoint coord, std::shared_ptr<Course::PlayerBase> owner_);

    /*
     * \brief deleteBuilding deletes the building in the highlighted position
     * \param pos of the building to be deleted
     * \return truth value whether deletion was succesful
     */
    bool deleteBuilding(QPoint pos);

    /*
     * \brief captureLand changes the owner of tiles to owner_ in radius given by size
     * \param coord position of the building that is used to capture land
     * \param size radius of the area to be captured
     * \param owner_ to who the area is captured
     */
    void captureLand(QPoint coord, int size, std::shared_ptr<Course::PlayerBase> owner_);

    //destructor
    ~BuildingHandler();

signals:
    void sendMessage(std::string&);

public slots:



private:
    Student::GameScene* scene_ = nullptr;
    std::shared_ptr<Student::ObjectManager> objmanager_ = nullptr;
    std::shared_ptr<Student::GameEventHandler> GEhandler_ = nullptr;
    const int MapitemID = 65537;
    QTimer *timer;


};
}
#endif // BUILDINGHANDLER_H
