#include "building_system.h"
#include "application.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"
#include <iostream>

void BuildingSystem::init() {
    m_render_event = std::bind(&BuildingSystem::on_render, this);

    m_mousedown_event = std::bind(&BuildingSystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&BuildingSystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void BuildingSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();

    event->register_handler(&m_render_event);
    mouseup_event->register_handler_priority(&m_mouseup_event);
    mousedown_event->register_handler_priority(&m_mousedown_event);

}

void BuildingSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();

    event->unregister_handler(&m_render_event);
    mouseup_event->unregister_handler(&m_mouseup_event);
    mousedown_event->unregister_handler(&m_mousedown_event);
}


bool BuildingSystem::on_mousedown(int x, int y, int button){
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();

    cm->begin<Building>();
    auto it = cm->next<Building>();

    while(it != nullptr){
        auto trans = em->get_component<Transform2D>(it->Entity);

        auto world_pos = world_to_screen(trans->position);

        if(x >= world_pos.x && x < world_pos.x + it->width){
            if(y >= world_pos.y && world_pos.y + it->height){

                auto evm = ecs::get_event_manager();

                if(button == 0) {
                    auto selected = evm->get_event<UnitSelected>();
                    selected->invoke(it->Entity);

                    std::cout << "Building selected: " << it->Entity << "\n";
                }else if(button == 1){
                    auto targeted = evm->get_event<UnitTargeted>();
                    targeted->invoke(it->Entity);

                    std::cout << "Building Targeted: " << it->Entity << "\n";
                }

                return true;
            }
        }

        it = cm->next<Building>();
    }

    return false;
}

bool BuildingSystem::on_mouseup(int x, int y, int button){
    return false;
}

void BuildingSystem::on_render() {
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();

    cm->begin<Building>();

    auto it = cm->next<Building>();

    while(it != nullptr){

        auto trans = em->get_component<Transform2D>(it->Entity);

        if(trans == nullptr) {
            it = cm->next<Building>();
            continue;
        }
        auto screen_pos = world_to_screen(trans->position);

        if(screen_pos.x < (-1 * it->width) || screen_pos.y < (-1 * it->height) || screen_pos.x > screen_width() || screen_pos.y > screen_height()) {
            it = cm->next<Building>();
            continue;
        }

        auto rend = get_renderer();
        rend->draw(it->animation_frames[it->current_frame], screen_pos);


        if(it->animation_speed < 0.0f)
        {
            it = cm->next<Building>();
            continue;
        }

        it->time_to_next_frame -= deltaTime();

        if(it->time_to_next_frame < 0.0f) {
            it->time_to_next_frame = it->animation_speed;
            it->current_frame++;

            if (it->current_frame >= it->animation_frames.size())
                it->current_frame = 0;
        }

        it = cm->next<Building>();
    }

}