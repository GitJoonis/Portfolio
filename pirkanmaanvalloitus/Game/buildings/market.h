#ifndef MARKET_H
#define MARKET_H


#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "core/resourcemaps.h"


namespace Student {

/**
 * @brief The Market class represents a market-building in the game.
 *
 * Market enables you to sell wood and stone
 * but now it is similar to the House building, conquers land in a radius of 1 tile, but it can only be built on sand
 */
class Market : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Market() = delete;

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
    explicit Market(
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
    virtual ~Market() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Market

} // namespace Student

#endif // MARKET_H
