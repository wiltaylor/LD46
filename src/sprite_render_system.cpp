#include "sprite_render_system.h"
#include "components.h"
#include "ecs/component.h"
#include "ecs/entity.h"
#include "ecs/event.h"
#include "events.h"
#include "platform/log.h"
#include "platform/renderer.h"
#include <iostream>

void SpriteRenderSystem::init(){
    m_renderhandler = std::bind(&SpriteRenderSystem::on_render, this);
    m_renderer = get_renderer();
}

void SpriteRenderSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->register_handler(&m_renderhandler);
}

void SpriteRenderSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->unregister_handler(&m_renderhandler);

}

void SpriteRenderSystem::on_render(){
    auto cm = ecs::get_component_manager();
    auto entm = ecs::get_entity_manager();

    cm->begin<SpriteRenderer>();

    auto it = cm->next<SpriteRenderer>();

    while(it != nullptr){

        auto transformId = entm->get_component_index<Transform2D>(it->Entity);
        if(transformId != nullptr){
            auto trans = cm->get_component<Transform2D>(*transformId);
            m_renderer->draw(it->AssetId, trans->position);
        }
        it = cm->next<SpriteRenderer>();
    }

}
