#include "test_system.h"
#include "ecs/component.h"
#include "ecs/event.h"
#include "ecs/entity.h"
#include "events.h"
#include "platform/log.h"
#include "components.h"
#include "platform/asset.h"
#include <iostream>

void TestSystem::init() {

    log_info("starting test system init");

    m_on_update = std::bind(&TestSystem::on_update, this);

    auto ent = ecs::get_entity_manager();
    auto cmp = ecs::get_component_manager();

    auto assetman =get_asset_manager();

    assetman->get_texture_asset("test.png", Global);

    cmp->register_component_type<Transform2D>(100);
    cmp->register_component_type<SpriteRenderer>(100);
    cmp->register_component_type<Camera2D>(1);

    auto e = ent->add_entity();

    auto trans = ent->add_component<Transform2D>(e);
    auto sprite = ent->add_component<SpriteRenderer>(e);

    trans->position.x = 50.0f;
    trans->position.y = 0.0f;
    trans->rotation = 0.0f;
   
}



void TestSystem::on_enable() {
    auto em = ecs::get_event_manager();
    auto sf = em->get_event<StartFrameEvent>();

    sf->register_handler(&m_on_update);
}

void TestSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto sf = em->get_event<StartFrameEvent>();

    sf->unregister_handler(&m_on_update);
}

void TestSystem::on_update() {
   
}
