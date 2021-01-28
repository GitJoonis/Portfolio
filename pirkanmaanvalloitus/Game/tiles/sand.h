#ifndef SAND_H
#define SAND_H


#include "tiles/tilebase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "core/resourcemaps.h"
#include "handlers/objectmanager.h"
#include "handlers/gameeventhandler.h"

namespace Student {

/*
 * \brief The Sand class is a variant of grassland tile. It is the only tile that market buildings can be built to.
 */
class Sand: public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;


    Sand() = delete;


    Sand(const Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3);


    //default destructor
    virtual ~Sand() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

}

#endif // SAND_H
