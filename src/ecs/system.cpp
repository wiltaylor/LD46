#include "system.h"

static unsigned int next_id = 0;
static ecs::SystemManager* current_instance = nullptr;

unsigned int ecs::SystemBase::nextID() {
    return next_id++;;
}

ecs::SystemManager* ecs::get_system_manager(){
    if(current_instance == nullptr)
        current_instance = new SystemManager();

    return current_instance;
}
