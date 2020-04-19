#include "input_system.h"
#include "ecs/event.h"
#include "events.h"
#include <functional>
#include "platform/log.h"
#include "components.h"

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

    switch(m_event.type) {
        case SDL_QUIT:
            quit();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT && !mouse_left_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseDownEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 0);
                mouse_left_down = true;
            }
            if (m_event.button.button == SDL_BUTTON_RIGHT && !mouse_right_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseDownEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 1);
                mouse_right_down = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (m_event.button.button == SDL_BUTTON_LEFT && mouse_left_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseUpEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 0);
                mouse_left_down = false;
            }
            if (m_event.button.button == SDL_BUTTON_RIGHT && mouse_right_down) {
                auto em = ecs::get_event_manager();
                auto event = em->get_event<MouseUpEvent>();
                event->invoke(m_event.button.x, m_event.button.y, 1);
                mouse_right_down = false;
            }
            break;
        case SDL_KEYDOWN:
            switch (m_event.key.keysym.sym) {
                case SDLK_DOWN: {
                    auto cm = ecs::get_component_manager();
                    cm->begin<Camera2D>();
                    auto cam = cm->next<Camera2D>();

                    cam->position.y += deltaTime * cam->scroll_speed;


                    if(cam->position.x < cam->min_position.x)
                        cam->position.x = cam->min_position.x;
                    if(cam->position.x > cam->max_position.x)
                        cam->position.x = cam->max_position.x;
                    if(cam->position.y < cam->min_position.y)
                        cam->position.y = cam->min_position.y;
                    if(cam->position.y > cam->max_position.y)
                        cam->position.y = cam->max_position.y;

                    break;
                }
                case SDLK_UP: {
                    auto cm = ecs::get_component_manager();
                    cm->begin<Camera2D>();
                    auto cam = cm->next<Camera2D>();

                    cam->position.y -= deltaTime * cam->scroll_speed;

                    if(cam->position.x < cam->min_position.x)
                        cam->position.x = cam->min_position.x;
                    if(cam->position.x > cam->max_position.x)
                        cam->position.x = cam->max_position.x;
                    if(cam->position.y < cam->min_position.y)
                        cam->position.y = cam->min_position.y;
                    if(cam->position.y > cam->max_position.y)
                        cam->position.y = cam->max_position.y;

                    break;
                }
                case SDLK_LEFT: {
                    auto cm = ecs::get_component_manager();
                    cm->begin<Camera2D>();
                    auto cam = cm->next<Camera2D>();

                    cam->position.x -= deltaTime * cam->scroll_speed;

                    if(cam->position.x < cam->min_position.x)
                        cam->position.x = cam->min_position.x;
                    if(cam->position.x > cam->max_position.x)
                        cam->position.x = cam->max_position.x;
                    if(cam->position.y < cam->min_position.y)
                        cam->position.y = cam->min_position.y;
                    if(cam->position.y > cam->max_position.y)
                        cam->position.y = cam->max_position.y;

                    break;
                }
                case SDLK_RIGHT: {
                    auto cm = ecs::get_component_manager();
                    cm->begin<Camera2D>();
                    auto cam = cm->next<Camera2D>();

                    cam->position.x += deltaTime * cam->scroll_speed;

                    if(cam->position.x < cam->min_position.x)
                        cam->position.x = cam->min_position.x;
                    if(cam->position.x > cam->max_position.x)
                        cam->position.x = cam->max_position.x;
                    if(cam->position.y < cam->min_position.y)
                        cam->position.y = cam->min_position.y;
                    if(cam->position.y > cam->max_position.y)
                        cam->position.y = cam->max_position.y;
                    break;
                }
                case SDLK_ESCAPE:
                    quit();
                    break;
            }
            break;
    }
}


