#include "bridge.h"

namespace Student{

Bridge::Bridge(const std::shared_ptr<Student::GameEventHandler> &eventhandler,
             const std::shared_ptr<Student::ObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             const int &tilespaces,
             const Course::ResourceMap &buildcost,
             const Course::ResourceMap &production):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production)

{
}


std::string Bridge::getType() const
{
    return "Bridge";
}


} //namespace Student

