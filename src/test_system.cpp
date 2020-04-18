#include "test_system.h"
#include "ecs/event.h"
#include "events.h"
#include "platform/log.h"

void TestSystem::init() {
    log_info("hit init");

    m_on_update = [](float value){  log_info("Updating..."); };



}

void TestSystem::on_enable() {
    log_info("Hit on enable");
    auto em = ecs::get_event_manager();
    auto sf = em->get_event<StartFrameEvent>();

    sf->register_handler(&m_on_update);
}

void TestSystem::on_disable() {
    log_info("hit disable");

    auto em = ecs::get_event_manager();
    auto sf = em->get_event<StartFrameEvent>();

    sf->unregister_handler(&m_on_update);
}
