#include "building_system.h"
#include "application.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"
#include <iostream>
#include "platform/asset.h"
void BuildingSystem::init() {
    m_render_event = std::bind(&BuildingSystem::on_render, this);

    auto assetman = get_asset_manager();
    m_monster1 = assetman->get_texture_asset("assets/monster_frame1.png", Global);
    m_monster2 = assetman->get_texture_asset("assets/monster_frame2.png", Global);
    m_burger1 = assetman->get_texture_asset("assets/burger_building.png", Global);

    m_on_spawn_event = std::bind(&BuildingSystem::on_spawn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    m_mousedown_event = std::bind(&BuildingSystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&BuildingSystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void BuildingSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto spawn_event = em->get_event<SpawnBuildingEvent>();

    event->register_handler(&m_render_event);
    mouseup_event->register_handler_priority(&m_mouseup_event);
    mousedown_event->register_handler_priority(&m_mousedown_event);
    spawn_event->register_handler(&m_on_spawn_event);

}

void BuildingSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto spawn_event = em->get_event<SpawnBuildingEvent>();

    event->unregister_handler(&m_render_event);
    mouseup_event->unregister_handler(&m_mouseup_event);
    mousedown_event->unregister_handler(&m_mousedown_event);
    spawn_event->unregister_handler(&m_on_spawn_event);
}

void BuildingSystem::on_spawn(BuildingType type, float x, float y){
    auto ent = ecs::get_entity_manager();

    switch(type){
        case BUILDING_Monster: {
            auto entity = ent->add_entity();
            auto building = ent->add_component<Building>(entity);
            auto trans = ent->add_component<Transform2D>(entity);

            building->animation_frames.push_back(m_monster1);
            building->animation_frames.push_back(m_monster2);
            building->hp = 100.0f;
            building->max_hp = 100.0f;
            building->hp_recovery = 0.01f;
            building->animation_speed = 2.0f;
            building->current_frame = 0;
            building->width = 200;
            building->height = 200;
            building->type = BUILDING_Monster;

            trans->position.x = x;
            trans->position.y = y;
            break;
        }
        case BUILDING_Burger: {
            auto entity = ent->add_entity();
            auto building = ent->add_component<Building>(entity);
            auto trans = ent->add_component<Transform2D>(entity);

            building->animation_frames.push_back(m_burger1);
            building->hp = 100.0f;
            building->max_hp = 100.0f;
            building->hp_recovery = 0.01f;
            building->animation_speed = -1.0f;
            building->current_frame = 0;
            building->width = 128;
            building->height = 128;
            building->type = BUILDING_Burger;

            trans->position.x = x;
            trans->position.y = y;
            break;
        }
    }
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