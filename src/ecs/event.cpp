#include "event.h"

static unsigned int next_id = 0;
static ecs::EventManager* single_instance = nullptr;

unsigned int ecs::EventBase::nextID() {
    return next_id++;
}

ecs::EventManager* ecs::get_event_manager() {
    if(single_instance == nullptr)
        single_instance = new ecs::EventManager();

    return single_instance;
}
