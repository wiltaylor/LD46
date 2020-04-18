#include "application.h"
#include "ecs/event.h"
#include "ecs/system.h"
#include "events.h"
#include "input_system.h"
#include "render_system.h"
#include "platform/log.h"
Application::Application(){
    log_info("Application starting up...");

    log_info("Registering global event handlers...");;
    auto em = ecs::get_event_manager();
    m_startFrame = em->get_event<StartFrameEvent>();
    m_startRender = em->get_event<StartRenderEvent>();
    m_endRender = em->get_event<EndRenderEvent>();
    m_shutdown = em->get_event<ShutdownEvent>();

    m_exitHandler = std::bind(&Application::onExit, this);
    m_shutdown->register_handler(&m_exitHandler);

    log_info("Registering systems");
    auto sm = ecs::get_system_manager();
    sm->register_system<RenderSystem>();
    sm->register_system<InputSystem>();

    log_info("Enabling systems");
    sm->enable<RenderSystem>();
    sm->enable<InputSystem>();
}

void Application::onExit(){

    log_info("Exit handler triggered");
    m_running = false;
}

Application::~Application(){

}

bool Application::onTick(float deltaTime){
    m_startFrame->invoke(deltaTime);

    m_startRender->invoke();
    m_endRender->invoke();

    return m_running;
}
