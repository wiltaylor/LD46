#include "test_system.h"
#include "ecs/component.h"
#include "ecs/event.h"
#include "ecs/entity.h"
#include "events.h"
#include "platform/log.h"
#include "components.h"
#include "platform/asset.h"
#include <iostream>
#include <stdlib.h>

void TestSystem::init() {

    log_info("starting test system init");

    m_on_update = std::bind(&TestSystem::on_update, this);

    auto ent = ecs::get_entity_manager();
    auto cmp = ecs::get_component_manager();

    auto assetman =get_asset_manager();

    auto sprite_id = assetman->get_texture_asset("assets/test.png", Global);
    auto tile_id = assetman->get_texture_asset("assets/tilemap.png", Global);


    cmp->register_component_type<Transform2D>(100);
    cmp->register_component_type<SpriteRenderer>(100);
    cmp->register_component_type<Camera2D>(1);
    cmp->register_component_type<TileMap>(1);


    auto cam = ent->add_entity();
    auto camcomp = ent->add_component<Camera2D>(cam);
    camcomp->position.x = 0.0f;
    camcomp->position.y = 0.0f;
    camcomp->width = 900.0f;
    camcomp->height = 600.0f;

    auto e = ent->add_entity();

    auto trans = ent->add_component<Transform2D>(e);
    auto sprite = ent->add_component<SpriteRenderer>(e);

    trans->position.x = 50.0f;
    trans->position.y = 0.0f;
    trans->rotation = 0.0f;

    sprite->AssetId = sprite_id;

    log_info("starting to load tilemap");

    auto tment = ent->add_entity();
    auto tm = ent->add_component<TileMap>(tment);
    auto ttran = ent->add_component<Transform2D>(tment);

    log_info("doot");

    tm->Texture = tile_id;
    tm->Width = 1000;
    tm->Height = 1000;
    tm->TileWidth = 32;
    tm->TileHeight = 32;
    tm->TextureWidth = 512;
    tm->TextureHeight = 512;

    ttran->position.x = 0.0f;
    ttran->position.y = 0.0f;
    ttran->rotation = 0.0f;

    for(auto i = 0; i < tm->Width * tm->Height; i++){
        tm->data.push_back(tile{0, false});
    }

    tm->data[2].tiletype = 1;
   
    log_info("Finished loading tilemap");
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
