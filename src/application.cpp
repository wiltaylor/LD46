#include "application.h"
#include "ecs/event.h"
#include "ecs/system.h"
#include "events.h"
#include "input_system.h"
#include "render_system.h"
#include "platform/log.h"
#include "test_system.h"
#include "sprite_render_system.h"
#include "tilemap_renderer_system.h"
#include "building_system.h"
#include "unit_system.h"
#include "ui_system.h"

static float current_delta_time;

float deltaTime() {
    return current_delta_time;
}

Application::Application(){
    log_info("Application starting up...");

    log_info("Registering global event handlers...");;
    auto em = ecs::get_event_manager();
    m_startFrame = em->get_event<StartFrameEvent>();
    m_startRender = em->get_event<StartRenderEvent>();
    m_render = em->get_event<RenderEvent>();
    m_endRender = em->get_event<EndRenderEvent>();
    m_shutdown = em->get_event<ShutdownEvent>();

    m_exitHandler = std::bind(&Application::onExit, this);
    m_shutdown->register_handler(&m_exitHandler);

    log_info("Registering systems");
    auto sm = ecs::get_system_manager();
    sm->register_system<RenderSystem>();
    sm->register_system<InputSystem>();
    sm->register_system<TestSystem>();
    sm->register_system<SpriteRenderSystem>();
    sm->register_system<TileMapRendererSystem>();
    sm->register_system<BuildingSystem>();
    sm->register_system<UnitSystem>();
    sm->register_system<UISystem>();

    log_info("Enabling systems");
    sm->enable<RenderSystem>();
    sm->enable<InputSystem>();
    sm->enable<TestSystem>();
    sm->enable<SpriteRenderSystem>();
    sm->enable<TileMapRendererSystem>();
    sm->enable<BuildingSystem>();
    sm->enable<UnitSystem>();
    sm->enable<UISystem>();
}

void Application::onExit(){

    log_info("Exit handler triggered");
    m_running = false;
}

Application::~Application(){

}

bool Application::onTick(float deltaTime){
    current_delta_time = deltaTime;
    m_startFrame->invoke(deltaTime);

    m_startRender->invoke();
    m_render->invoke();
    m_endRender->invoke();

    return m_running;
}
