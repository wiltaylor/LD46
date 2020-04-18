#include "input_system.h"
#include "ecs/event.h"
#include "events.h"
#include <functional>
#include "platform/log.h"

void InputSystem::init() {
    m_startframe = std::bind(&InputSystem::on_update, this, std::placeholders::_1);
}

void InputSystem::on_enable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<StartFrameEvent>();
    event->register_handler(&m_startframe);
}

void InputSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<StartFrameEvent>();
    event->unregister_handler(&m_startframe);
}

void InputSystem::on_update(float deltaTime) {

    SDL_WaitEvent(&m_event);

    switch(m_event.type){
        case SDL_QUIT:
            std::abort();
            break;
        case SDL_KEYDOWN:
            switch(m_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    std::abort();
                    break;
            }
            break;
    }
}


