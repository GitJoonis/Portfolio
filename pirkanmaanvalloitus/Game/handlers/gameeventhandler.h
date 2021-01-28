#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include "core/playerbase.h"
#include "core/basicresources.h"
#include "tiles/grassland.h"
#include "interfaces/igameeventhandler.h"
#include <QtCore>





using PlayerBase = Course::PlayerBase;
using BasicResource = Course::BasicResource;
using ResourceMap = Course::ResourceMap;
using Coordinate = Course::Coordinate;

namespace Student {

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();

    ~GameEventHandler()
    {

    }

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(std::shared_ptr<PlayerBase> player,
                                BasicResource resource,
                                int amount);

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(std::shared_ptr<PlayerBase> player,
                         Course::ResourceMap resources);
    /*
     * \brief getResource returns the amount of resource the player has
     * \param resource gives the resource which is returned
     * \return amount of given resource as an integer
     */
    int getResource(BasicResource resource);

    /*
     * \brief compareResources compares two resourcemaps to make sure that the player has enough of resources to build
     * \param compared is the resource map to which the players resources are compared
     * \return truth value whether the player has more resources than is required to build
     */
    bool compareResources(Course::ResourceMap compared);

    /*
     * \brief getResources returns all the players resources as a resourcemap
     * \return resourcemap that contains the players resources
     */
    Course::ResourceMap getResources();


private:
    Course::ResourceMap resources_;


};

} //namespace Student
#endif // GAMEEVENTHANDLER_H
