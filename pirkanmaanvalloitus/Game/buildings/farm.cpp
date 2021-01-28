#include "farm.h"

namespace Student{

Farm::Farm(const std::shared_ptr<Student::GameEventHandler> &eventhandler,
             const std::shared_ptr<Student::ObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             const int &tilespaces):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces)

{
}


std::string Farm::getType() const
{
    return "Farm";
}


} //namespace Student

