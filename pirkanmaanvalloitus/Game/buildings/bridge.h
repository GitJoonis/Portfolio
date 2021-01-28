#ifndef BRIDGE_H
#define BRIDGE_H


#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "core/resourcemaps.h"


namespace Student {

/**
 * @brief The Bridge class represents a bridge-building in the game.
 *
 * bridge is the only building that can be built in water. Conquers land in a radius of 1 tile.
 */
class Bridge : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Bridge() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit Bridge(
            const std::shared_ptr<Student::GameEventHandler>& eventhandler,
            const std::shared_ptr<Student::ObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::FARM_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::FARM_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Bridge() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Bridge

} // namespace Student

#endif // BRIDGE_H
