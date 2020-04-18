#include <iostream>
#include "../log.h"
#include "../../events.h"
#include "../../test_system.h"
#include "../../render_system.h"
#include "../renderer.h"
#include "../../input_system.h"

int main(int argc, char *argv[]) {

    auto em = ecs::get_event_manager();
    auto sm = ecs::get_system_manager();

    auto update_event = em->get_event<StartFrameEvent>();
    auto render_begin = em->get_event<StartRenderEvent>();
    auto render_end = em->get_event<EndRenderEvent>();

//    sm->register_system<TestSystem>();
  //  sm->enable<TestSystem>();

    sm->register_system<RenderSystem>();
    sm->enable<RenderSystem>();

    sm->register_system<InputSystem>();
    sm->enable<InputSystem>();


    while(true) {
        update_event->invoke(0); // Launch start frameevent

        render_begin->invoke();
        render_end->invoke();

        //Physics/logic

        //Renderer


        //End of frame event



    }
}
