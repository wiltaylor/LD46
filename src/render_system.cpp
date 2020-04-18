#include "render_system.h"
#include "ecs/event.h"
#include "events.h"
#include "platform/renderer.h"

void RenderSystem::init(){

    m_renderer = get_renderer();

    m_startrender = std::bind(&RenderSystem::on_start, this);
    m_endrender = std::bind(&RenderSystem::on_end, this);
}

void RenderSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto start = em->get_event<StartRenderEvent>();
    auto finish = em->get_event<EndRenderEvent>();

    start->register_handler(&m_startrender);
    finish->register_handler(&m_endrender);

}

void RenderSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto start = em->get_event<StartRenderEvent>();
    auto finish = em->get_event<EndRenderEvent>();

    start->unregister_handler(&m_startrender);
    finish->unregister_handler(&m_endrender);

}

void RenderSystem::on_start(){
    m_renderer->begin();
}

void RenderSystem::on_end(){
    m_renderer->end();
}
