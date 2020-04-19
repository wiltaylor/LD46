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

void quit(){
    log_info("Quit called!");
    auto em = ecs::get_event_manager();
    auto sd = em->get_event<ShutdownEvent>();
    sd->invoke();
}

void InputSystem::on_update(float deltaTime) {

    static bool mouse_left_down = false;
    static bool mouse_right_down = false;

    SDL_PollEvent(&m_event);

    switch(m_event.type){
        case SDL_QUIT:
            quit();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(m_event.button.button == SDL_BUTTON_LEFT && !mouse_left_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseDownEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 0);
                mouse_left_down = true;
            }
            if(m_event.button.button == SDL_BUTTON_RIGHT && !mouse_right_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseDownEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 1);
                mouse_right_down = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(m_event.button.button == SDL_BUTTON_LEFT && mouse_left_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseUpEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 0);
                mouse_left_down = false;
            }
            if(m_event.button.button == SDL_BUTTON_RIGHT && mouse_right_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseUpEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 1);
                mouse_right_down = false;
            }
            break;
        case SDL_KEYDOWN:
            switch(m_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit();
                    break;
            }
            break;
    }
}


