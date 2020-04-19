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

    auto tile_id = assetman->get_texture_asset("assets/tilemap.png", Global);
    auto worker_up_id = assetman->get_texture_asset("assets/worker_up.png", Global);
    auto worker_down_id = assetman->get_texture_asset("assets/worker_down.png", Global);
    auto worker_left_id = assetman->get_texture_asset("assets/worker_left.png", Global);
    auto worker_right_id = assetman->get_texture_asset("assets/worker_right.png", Global);

    auto monster1_id = assetman->get_texture_asset("assets/monster_frame1.png", Global);
    auto monster2_id = assetman->get_texture_asset("assets/monster_frame2.png", Global);

    auto burger_id = assetman->get_texture_asset("assets/burger_building.png", Global);

    cmp->register_component_type<Transform2D>(100);
    cmp->register_component_type<SpriteRenderer>(100);
    cmp->register_component_type<Camera2D>(1);
    cmp->register_component_type<TileMap>(1);
    cmp->register_component_type<Building>(20);
    cmp->register_component_type<Collider>(100);
    cmp->register_component_type<Unit>(100);
    cmp->register_component_type<UnitAI>(100);

    auto cam = ent->add_entity();
    auto camcomp = ent->add_component<Camera2D>(cam);
    camcomp->position.x = 0.0f;
    camcomp->position.y = 0.0f;
    camcomp->width = 900.0f;
    camcomp->height = 600.0f;
    camcomp->max_position.x = 32 * 100 - 900.0f;
    camcomp->max_position.y = 32 * 100 - 600.0f;
    camcomp->min_position.x = 0.0f;
    camcomp->min_position.y = 0.0f;
    camcomp->scroll_speed = 500.0f;

    auto monster = ent->add_entity();
    auto building = ent->add_component<Building>(monster);
    auto monster_trans = ent->add_component<Transform2D>(monster);

    building->animation_frames.push_back(monster1_id);
    building->animation_frames.push_back(monster2_id);
    building->hp = 100.0f;
    building->max_hp = 100.0f;
    building->hp_recovery = 0.01f;
    building->animation_speed = 2.0f;
    building->current_frame = 0;
    building->width = 200;
    building->height = 200;
    building->type = BUILDING_Monster;

    monster_trans->position.x = 20.0f;
    monster_trans->position.y = 20.0f;


    auto burger_joint = ent->add_entity();
    auto burger_building = ent->add_component<Building>(burger_joint);
    auto burger_trans = ent->add_component<Transform2D>(burger_joint);

    burger_building->animation_frames.push_back(burger_id);

    burger_building->hp = 100.0f;
    burger_building->max_hp = 100.0f;
    burger_building->hp_recovery = 0.1f;
    burger_building->animation_speed = -1.0f;
    burger_building->current_frame = 0;
    burger_building->width = 128;
    burger_building->height = 128;
    burger_building->type = BUILDING_Burger;

    burger_trans->position.x = 800.0f;
    burger_trans->position.y = 200.0f;

    auto bob = ent->add_entity();
    auto bob_unit = ent->add_component<Unit>(bob);
    auto bob_trans = ent->add_component<Transform2D>(bob);
    auto bob_ai = ent->add_component<UnitAI>(bob);

    bob_unit->up_texture = worker_up_id;
    bob_unit->down_texture = worker_down_id;
    bob_unit->left_texture = worker_left_id;
    bob_unit->right_texture = worker_right_id;
    bob_unit->direction = UNIT_DOWN;
    bob_unit->width = 64;
    bob_unit->height = 64;
    bob_unit->speed = 40.0f;
    bob_unit->type = UNIT_Cultist;
    bob_unit->hide = false;

    bob_trans->position.x = 600.0f;
    bob_trans->position.y = 200.0f;

    bob_ai->target.x = 900;
    bob_ai->target.y = 600;
    bob_ai->state = AI_MOVE;
    bob_ai->hide_timeout = 5.0f;

    log_info("starting to load tilemap");

    auto tment = ent->add_entity();
    auto tm = ent->add_component<TileMap>(tment);
    auto ttran = ent->add_component<Transform2D>(tment);

    log_info("doot");

    tm->Texture = tile_id;
    tm->Width = 100;
    tm->Height = 100;
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
    tm->data[99].tiletype = 2;
   
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
