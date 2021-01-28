#ifndef WATER_H
#define WATER_H


#include "tiles/tilebase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "core/resourcemaps.h"
#include "handlers/objectmanager.h"
#include "handlers/gameeventhandler.h"

namespace Student {

/*
 * \brief The Water class is a tile that can be used to divide the map in different islands.
 */
class Water: public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;


    Water() = delete;


    Water(const Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3);


    //default destructor
    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

}


#endif // WATER_H

