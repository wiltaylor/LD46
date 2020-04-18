#include <iostream>
#include "../log.h"
#include "../../ecs/event.h"
#include "../../events.h"
#include "../../test_system.h"

int main(int argc, char *argv[]) {

    auto em = ecs::get_event_manager();
    auto sm = ecs::get_system_manager();

    auto update_event = em->get_event<StartFrameEvent>();

    sm->register_system<TestSystem>();
    sm->enable<TestSystem>();

    while(true) {
        update_event->invoke(0); // Launch start frameevent

        //Physics/logic

        //Renderer


        //End of frame event



    }
}
