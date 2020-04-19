#include "unit_system.h"
#include "ecs/entity.h"
#include "platform/renderer.h"
#include "coords.h"

void UnitSystem::init() {
    m_render_event = std::bind(&UnitSystem::on_render, this);
    m_update_event = std::bind(&UnitSystem::on_update, this, std::placeholders::_1);

    m_mousedown_event = std::bind(&UnitSystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&UnitSystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void UnitSystem::on_enable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    event->register_handler(&m_render_event);
    update_event->register_handler(&m_update_event);
    mouseup_event->register_handler_priority(&m_mouseup_event);
    mousedown_event->register_handler_priority(&m_mousedown_event);
}

void UnitSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto update_event = em->get_event<StartFrameEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    event->unregister_handler(&m_render_event);
    update_event->unregister_handler(&m_update_event);
    mouseup_event->unregister_handler(&m_mouseup_event);
    mousedown_event->unregister_handler(&m_mousedown_event);
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