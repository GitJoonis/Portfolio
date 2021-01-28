#ifndef FarmReadyREADY_H
#define FarmReadyREADY_H


#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "handlers/gameeventhandler.h"
#include "handlers/objectmanager.h"
#include "core/resourcemaps.h"


namespace Student {

/**
 * @brief The Farm class represents a Farm-building in the game.
 * gives the player 100 food, but does not conquer any land
 * can be built on grassland
 */
class Farm : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Farm() = delete;

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
    explicit Farm(
            const std::shared_ptr<Student::GameEventHandler>& eventhandler,
            const std::shared_ptr<Student::ObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1);

    /**
     * @brief Default destructor.
     */
    virtual ~Farm() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Farm

} // namespace Student

#endif // FarmReadyREADY_H
