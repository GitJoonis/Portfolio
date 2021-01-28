#include "gameeventhandler.h"

namespace Student {


GameEventHandler::GameEventHandler()
{

}

bool GameEventHandler::compareResources(Course::ResourceMap compared){
    for(auto it = compared.begin(); it != compared.end(); it++){
        if(-(*it).second > resources_[(*it).first]){           
            return 0;
        }
    }
    return 1;

}


bool GameEventHandler::modifyResource(std::shared_ptr<PlayerBase> player, BasicResource resource, int amount)
{
    Q_UNUSED(player)
    if(resources_[resource] + amount < 0){
        return 0;
    }
    else{
        resources_[resource] += amount;
        return 1;

    }
}

bool GameEventHandler::modifyResources(std::shared_ptr<PlayerBase> player, ResourceMap resources)
{
    if(compareResources(resources)){
        Q_UNUSED(player)
        for(auto it = resources.begin(); it != resources.end(); it++){
            resources_[(*it).first] += (*it).second;
        }
        return 1;
    }
    else{
        return 0;
    }

}

int GameEventHandler::getResource(BasicResource resource)
{
    return resources_[resource];
}

Course::ResourceMap GameEventHandler::getResources()
{
    return resources_;
}






}//namespace

