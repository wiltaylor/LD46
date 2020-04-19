#include "building_system.h"
#include "application.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"
#include <iostream>

void BuildingSystem::init() {
    m_render_event = std::bind(&BuildingSystem::on_render, this);
}

void BuildingSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->register_handler(&m_render_event);
}

void BuildingSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->unregister_handler(&m_render_event);
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