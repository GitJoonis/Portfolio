#ifndef HOUSE_H
#define HOUSE_H

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "core/resourcemaps.h"


namespace Student {

/**
 * @brief The House class represents a farm-building in the game.
 *  Houses conquer land in a radius of 1 tile
 *  can be built on both sand and water
 */
class House : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    House() = delete;

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
    explicit House(
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
    virtual ~House() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class House

} // namespace Student


#endif // HOUSE_H
