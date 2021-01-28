#include "stone.h"
#include "tiles/tilebase.h"

namespace Student {


Stone::Stone(const Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work):

    TileBase(location,
             eventhandler,
             objectmanager,
             max_build,
             max_work)
{
}

std::string Stone::getType() const
{
    return "Stone";
}

}
