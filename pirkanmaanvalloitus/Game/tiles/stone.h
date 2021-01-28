#ifndef STONE_H
#define STONE_H


#include "tiles/tilebase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "core/resourcemaps.h"
#include "handlers/objectmanager.h"
#include "handlers/gameeventhandler.h"

namespace Student {

/*
 * \brief The Stone class was supposed to give the player the possibility to gather stone
 */
class Stone: public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;


    Stone() = delete;


    Stone(const Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3);


    //default destructor
    virtual ~Stone() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

}


#endif // STONE_H
