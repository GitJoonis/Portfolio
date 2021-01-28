#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "interfaces/iobjectmanager.h"
#include <map>
#include "tiles/tilebase.h"
#include "graphics/mapitem.h"
#include "core/playerbase.h"


using ObjectId = unsigned int;
using Coordinate = Course::Coordinate;
using TileBase = Course::TileBase;
using BuildingBase = Course::BuildingBase;
using WorkerBase = Course::WorkerBase;

namespace Student {


class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();

    ~ObjectManager();

    QPoint toIsometric(Course::Coordinate& point);

    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles a vector that contains the Tiles to be added.
     * @post The tile-pointers in the vector are stored in the ObjectManager.
     * Exception Guarantee: Basic
     *
     */
    void addTiles(const std::vector<std::shared_ptr<TileBase> > &tiles) override;

    /**
     * @brief Adds new graphics to the ObjectManager.
     * @param tile_graphics a vector that contains the Tiles to be added.
     * @post The tile-pointers in the vector are stored in the ObjectManager.
     *
     */
    void addTileGraphics(const std::vector<Student::MapItem*> &tile_graphics);

    /**
     * @brief Adds new tile to the ObjectManager.
     * @param tile to be added
     * @post The tile is stored in the ObjectManager.
     *
     */
    void addTile(std::shared_ptr<TileBase> &tile);


    /**
     * @brief Adds new graphic tile to the ObjectManager.
     * @param tile to be added
     * @post The tile is stored in the ObjectManager.
     *
     */
    void addGraphic(Student::MapItem* item);

    /**
     * @brief Adds new building to the ObjectManager.
     * @param building to be added
     * @post The building is stored in the ObjectManager.
     *
     */
    void addBuilding(std::shared_ptr<BuildingBase> &building);

    /**
     * @brief Returns a shared pointer to a Tile that has specified coordinate.
     * @param coordinate Requested Tile's Coordinate
     * @return a pointer to a Tile that has the given coordinate.
     * If no for the coordinate exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<TileBase> getTile(const Coordinate &coordinate) override;

    /**
     * @brief Returns a shared pointer to a Tile that has specified ID
     * @param id Tile's ObjectId.
     * @return a pointer to the Tile that has the given ID
     * If no for the id exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<TileBase> getTile(const ObjectId &id) override;

    /**
     * @brief Returns a vector of shared pointers to Tiles specified by
     * a vector of Coordinates.
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector of that contains pointers to Tile's that match
     * the coordinates. The vector is empty if no matches were made.
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<TileBase> > getTiles(const std::vector<Coordinate> &coordinates) override;

    /**
     * @brief return the progress of conquered non-water tiles
     * @param owner for which the progress is checked
     * @return int that represents the percentage of conquered land
     *
     */
    int getProgress(std::shared_ptr<Course::PlayerBase> owner);

    /*
     * \brief gatherResources is used to gather resources based on how many forest or stone tiles are owned by the player
     * \param owner player for which the tiles are searched
     * \param type type of the resource
     * \return integer containing the amount of resources to be added
     */
    int gatherResources(std::shared_ptr<Course::PlayerBase> owner, std::string type);

private:
    std::vector<std::shared_ptr<BuildingBase>> buildings_;
    std::vector<std::shared_ptr<TileBase>> tiles_;
    std::vector<Student::MapItem*> graphics_;
};
}
#endif
