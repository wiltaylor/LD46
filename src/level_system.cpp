#include "level_system.h"
#include "components.h"
#include "platform/asset.h"
#include "ecs/entity.h"

void LevelSystem::init() {
    m_load_level_event = std::bind(&LevelSystem::on_load_level, this, std::placeholders::_1);

    auto assetman = get_asset_manager();
    m_tilemap_texture = assetman->get_texture_asset("assets/tilemap.png", Global);

}

void LevelSystem::on_enable() {
    auto em =  ecs::get_event_manager();
    auto event = em->get_event<LoadLevelEvent>();
    event->register_handler(&m_load_level_event);
}

void LevelSystem::on_disable() {
    auto em = ecs::get_event_manager();
    auto event = em->get_event<LoadLevelEvent>();
    event->unregister_handler(&m_load_level_event);
}

void LevelSystem::build_camera(){
    auto ent = ecs::get_entity_manager();
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
}

void LevelSystem::clear_level(){
    auto ent = ecs::get_entity_manager();
    ent->clear_all();
}

void LevelSystem::new_tilemap(int width, int height, unsigned int default_tile){
    auto entman = ecs::get_entity_manager();
    auto entity = entman->add_entity();
    auto tmap = entman->add_component<TileMap>(entity);
    auto trans = entman->add_component<Transform2D>(entity);

    tmap->Texture = m_tilemap_texture;
    tmap->Width = width;
    tmap->Height = height;
    tmap->TileWidth = 32;
    tmap->TileHeight = 32;
    tmap->TextureWidth = 512;
    tmap->TextureHeight = 512;

    trans->position.x = 0.0f;
    trans->position.y = 0.0f;
    trans->rotation = 0.0f;

    for(auto i = 0; i < tmap->Width * tmap->Height; i++){
        tmap->data.push_back(tile{default_tile, false});
    }
}

void LevelSystem::on_load_level(unsigned int index){
    auto em = ecs::get_event_manager();
    auto unit_spawn = em->get_event<SpawnUnitEvent>();
    auto building_spawn = em->get_event<SpawnBuildingEvent>();

    clear_level();
    build_camera();

    switch(index){
        case 1:
            new_tilemap(100, 100, 0);
            unit_spawn->invoke(UNIT_Cultist, 600.0f, 200.0f);
            building_spawn->invoke(BUILDING_Monster, 20.0f, 20.0f);
            building_spawn->invoke(BUILDING_Burger, 800.0f, 200.0f);
            break;
    }
}