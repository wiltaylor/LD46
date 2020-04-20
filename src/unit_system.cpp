#include "unit_system.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"
#include "platform/asset.h"
#include <iostream>
void UnitSystem::init() {
    m_render_event = std::bind(&UnitSystem::on_render, this);
    m_update_event = std::bind(&UnitSystem::on_update, this, std::placeholders::_1);
    m_spawn_event = std::bind(&UnitSystem::on_spawn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    m_targeted_event = std::bind(&UnitSystem::on_targeted, this, std::placeholders::_1);
    m_selected_event = std::bind(&UnitSystem::on_selected, this, std::placeholders::_1);

    m_mousedown_event = std::bind(&UnitSystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&UnitSystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);


    auto assetman =get_asset_manager();

    m_worker_up_id = assetman->get_texture_asset("assets/worker_up.png", Global);
    m_worker_down_id = assetman->get_texture_asset("assets/worker_down.png", Global);
    m_worker_left_id = assetman->get_texture_asset("assets/worker_left.png", Global);
    m_worker_right_id = assetman->get_texture_asset("assets/worker_right.png", Global);
}

void UnitSystem::on_enable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto targeted_event = em->get_event<UnitTargeted>();
    auto selected_event = em->get_event<UnitSelected>();
    auto spawn_event = em->get_event<SpawnUnitEvent>();

    event->register_handler(&m_render_event);
    update_event->register_handler(&m_update_event);
    mouseup_event->register_handler_priority(&m_mouseup_event);
    mousedown_event->register_handler_priority(&m_mousedown_event);
    targeted_event->register_handler(&m_targeted_event);
    selected_event->register_handler(&m_selected_event);
    spawn_event->register_handler(&m_spawn_event);
}

void UnitSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto targeted_event = em->get_event<UnitTargeted>();
    auto selected_event = em->get_event<UnitSelected>();
    auto spawn_event = em->get_event<SpawnUnitEvent>();

    event->unregister_handler(&m_render_event);
    update_event->unregister_handler(&m_update_event);
    mouseup_event->unregister_handler(&m_mouseup_event);
    mousedown_event->unregister_handler(&m_mousedown_event);
    targeted_event->unregister_handler(&m_targeted_event);
    selected_event->unregister_handler(&m_selected_event);
    spawn_event->unregister_handler(&m_spawn_event);
}

void UnitSystem::on_spawn(UnitType type, float x, float y){
    auto ent = ecs::get_entity_manager();
    auto entity = ent->add_entity();
    auto unit = ent->add_component<Unit>(entity);
    auto trans = ent->add_component<Transform2D>(entity);
    auto ai = ent->add_component<UnitAI>(entity);

    std::cout << "triggered spawn\n" ;

    switch(type){
        case UNIT_Cultist: {
            unit->up_texture = m_worker_up_id;
            unit->down_texture = m_worker_down_id;
            unit->right_texture = m_worker_right_id;
            unit->left_texture = m_worker_left_id;
            unit->direction = UNIT_DOWN;
            unit->width = 64;
            unit->height = 64;
            unit->speed = 60.0f;
            unit->type = UNIT_Cultist;
            unit->hide = false;

            trans->position.x = x;
            trans->position.y = y;

            ai->state = AI_IDLE;
            ai->hide_timeout = 5.0f;
            break;
        }
        case UNIT_Wizard: {
            break;
        }
        case UNIT_Enemy: {
            break;
        }
    }
}

void UnitSystem::on_targeted(unsigned int entity){

    if(entity == 0)
        return;

    auto ent = ecs::get_entity_manager();

    auto selected_unit = ent->get_component<Unit>(m_selected_unit);
    if(selected_unit == nullptr)
        return;

    if(selected_unit->type == UNIT_Cultist){
        auto building = ent->get_component<Building>(entity);
        auto building_trans = ent->get_component<Transform2D>(entity);

        if(building == nullptr)
            return;

        if(building->type != BUILDING_Burger)
            return;

        auto ai = ent->get_component<UnitAI>(m_selected_unit);

        ai->state = AI_GATHER;
        ai->harvest_entity = building->Entity;
        ai->target.x = building_trans->position.x + building->width / 2;
        ai->target.y = building_trans->position.y + building->height / 2;
    }

}

void UnitSystem::on_selected(unsigned int entity){
    m_selected_unit = entity;
}

bool UnitSystem::on_mousedown(int x, int y, int button){
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();

    cm->begin<Unit>();
    auto it = cm->next<Unit>();

    while(it != nullptr){
        auto trans = em->get_component<Transform2D>(it->Entity);

        auto world_pos = world_to_screen(trans->position);

        if(x >= world_pos.x && x < world_pos.x + it->width){
            if(y >= world_pos.y && world_pos.y + it->height){

                auto evm = ecs::get_event_manager();

                if(button == 0) {
                    auto selected = evm->get_event<UnitSelected>();
                    selected->invoke(it->Entity);

                    std::cout << "Entity selected: " << it->Entity << "\n";
                }else if(button == 1){
                    auto targeted = evm->get_event<UnitTargeted>();
                    targeted->invoke(it->Entity);

                    std::cout << "Entity Targeted: " << it->Entity << "\n";
                }

                return true;
            }
        }

        it = cm->next<Unit>();
    }

    return false;
}

bool UnitSystem::on_mouseup(int x, int y, int button){
    return false;
}

void UnitSystem::on_update(float delta_time){
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();
    auto env = ecs::get_event_manager();

    cm->begin<UnitAI>();
    auto it = cm->next<UnitAI>();

    while(it != nullptr){
        auto trans = em->get_component<Transform2D>(it->Entity);
        auto unit = em->get_component<Unit>(it->Entity);

        switch(it->state){
            case AI_IDLE:
                break;
            case AI_GATHER: {
                float move_delta_x = unit->speed * delta_time;
                float move_delta_y = unit->speed * delta_time;

                if (trans->position.x > it->target.x)
                    move_delta_x *= -1;
                if (trans->position.y > it->target.y)
                    move_delta_y *= -1;

                if (glm::distance(trans->position, it->target) < 1.5f){
                    it->current_hide = it->hide_timeout;
                    it->state = AI_WAITING_ON_ORDER;
                }

                trans->position.x += move_delta_x;
                trans->position.y += move_delta_y;

                break;
            }

            case AI_RETURN:{
                float move_delta_x = unit->speed * delta_time;
                float move_delta_y = unit->speed * delta_time;

                if (trans->position.x > it->target.x)
                    move_delta_x *= -1;
                if (trans->position.y > it->target.y)
                    move_delta_y *= -1;

                if (glm::distance(trans->position, it->target) < 100.0f){
                    it->state = AI_GATHER;

                    auto trans = em->get_component<Transform2D>(it->harvest_entity);
                    auto build = em->get_component<Building>(it->harvest_entity);

                    it->target.x = trans->position.x + build->width / 2;
                    it->target.y = trans->position.y + build->height / 2;
                }

                trans->position.x += move_delta_x;
                trans->position.y += move_delta_y;

                break;
            }

            case AI_WAITING_ON_ORDER: {
                auto unit = em->get_component<Unit>(it->Entity);

                if(m_selected_unit == it->Entity){
                    auto event = env->get_event<UnitSelected>();
                    event->invoke(0);
                }

                it->current_hide -= delta_time;

                if(it->current_hide < 0.0f)
                {
                    it->state = AI_RETURN;
                    unit->hide = false;

                    cm->begin<Building>();
                    auto monster = cm->next<Building>();

                    while(monster != nullptr){
                        if(monster->type == BUILDING_Monster) {
                            auto monster_trans = em->get_component<Transform2D>(monster->Entity);

                            it->target.x = monster_trans->position.x + (monster->width / 2);
                            it->target.y = monster_trans->position.y + (monster->height / 2);

                            return;
                        }
                    }

                    //Can't find monster.
                    it->state = AI_IDLE;

                    break;
                }

                unit->hide = true;
                break;
            }
            case AI_MOVE: {
                float move_delta_x = unit->speed * delta_time;
                float move_delta_y = unit->speed * delta_time;

                if (trans->position.x > it->target.x)
                    move_delta_x *= -1;
                if (trans->position.y > it->target.y)
                    move_delta_y *= -1;

                if (glm::distance(trans->position, it->target) < 0.5f)
                    it->state = AI_IDLE;

                trans->position.x += move_delta_x;
                trans->position.y += move_delta_y;

                break;
            }
        }

        it = cm->next<UnitAI>();
    }
}

void UnitSystem::on_render(){
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();

    cm->begin<Unit>();

    auto it = cm->next<Unit>();

    while(it != nullptr) {

        if(it->hide){
            it = cm->next<Unit>();
            continue;
        }

        auto trans = em->get_component<Transform2D>(it->Entity);

        if(trans == nullptr) {
            it = cm->next<Unit>();
            continue;
        }

        auto screen_pos = world_to_screen(trans->position);

        if(screen_pos.x < (-1 * it->width) || screen_pos.y < (-1 * it->height) || screen_pos.x > screen_width() || screen_pos.y > screen_height()){
            it = cm->next<Unit>();
            continue;
        }

        auto rend = get_renderer();
        unsigned int image = 0;

        switch(it->direction){
            case UNIT_UP:
                image = it->up_texture;
                break;
            case UNIT_DOWN:
                image = it->down_texture;
                break;
            case UNIT_LEFT:
                image = it->left_texture;
                break;
            case UNIT_RIGHT:
                image = it->right_texture;
                break;
        }

        rend->draw(image, screen_pos);

        it = cm->next<Unit>();

    }
}