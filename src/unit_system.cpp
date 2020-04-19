#include "unit_system.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"

void UnitSystem::init() {
    m_render_event = std::bind(&UnitSystem::on_render, this);
    m_update_event = std::bind(&UnitSystem::on_update, this, std::placeholders::_1);
}

void UnitSystem::on_enable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    event->register_handler(&m_render_event);
    update_event->register_handler(&m_update_event);
}

void UnitSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    event->unregister_handler(&m_render_event);
    update_event->unregister_handler(&m_update_event);
}

void UnitSystem::on_update(float delta_time){
    auto cm = ecs::get_component_manager();
    auto em = ecs::get_entity_manager();

    cm->begin<UnitAI>();
    auto it = cm->next<UnitAI>();

    while(it != nullptr){
        auto trans = em->get_component<Transform2D>(it->Entity);
        auto unit = em->get_component<Unit>(it->Entity);

        switch(it->state){
            case AI_IDLE:
                break;
            case AI_MOVE:
                float move_delta_x = unit->speed * delta_time;
                float move_delta_y = unit->speed * delta_time;

                if(trans->position.x > it->target.x)
                    move_delta_x *= -1;
                if(trans->position.y > it->target.y)
                    move_delta_y *= -1;

                if(glm::distance(trans->position, it->target) < 0.1f)
                    it->state = AI_IDLE;

                trans->position.x += move_delta_x;
                trans->position.y += move_delta_y;

                break;
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