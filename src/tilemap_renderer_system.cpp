#include "tilemap_renderer_system.h"
#include "events.h"
#include "components.h"
#include "ecs/entity.h"
#include <iostream>
#include <glm/glm.hpp>
#include "tilemap.h"
#include <assert.h>
#include "coords.h"

void TileMapRendererSystem::init(){
    m_render_event = std::bind(&TileMapRendererSystem::on_render, this);
    m_mousedown_event = std::bind(&TileMapRendererSystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&TileMapRendererSystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    m_renderer = get_renderer();

    std::cout << "loaded tilemap renderer\n";
}

void TileMapRendererSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->register_handler(&m_render_event);

    auto mouseup_event = em->get_event<MouseUpEvent>();
    mouseup_event->register_handler(&m_mouseup_event);

    auto mousedown_event = em->get_event<MouseDownEvent>();
    mousedown_event->register_handler(&m_mousedown_event);
}

void TileMapRendererSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->unregister_handler(&m_render_event);

    auto mouseup_event = em->get_event<MouseUpEvent>();
    mouseup_event->unregister_handler(&m_mouseup_event);

    auto mousedown_event = em->get_event<MouseDownEvent>();
    mousedown_event->unregister_handler(&m_mousedown_event);
}

bool TileMapRendererSystem::on_mousedown(int x, int y, int button) {
    auto cm = ecs::get_component_manager();
    auto ent = ecs::get_entity_manager();

    cm->begin<Camera2D>();
    auto cam = cm->next<Camera2D>();
    assert(cam != nullptr);

    cm->begin<TileMap>();

    auto it = cm->next<TileMap>();

    while(it != nullptr){

        auto trans = ent->get_component<Transform2D>(it->Entity);

        auto top_left = world_to_screen(trans->position);
        auto click_spot = world_to_local(screen_to_world(glm::vec2(x, y)), trans->position);

        if(trans != nullptr){
            if(top_left.x > screen_width())
                continue;

            if(top_left.y > screen_height())
                continue;

            if(top_left.x + it->Width * it->TileWidth < 0)
                continue;

            if(top_left.y + it->Height * it->TileHeight < 0)
                continue;

            int x_tile = click_spot.x / it->TileWidth;
            int y_tile = click_spot.y / it->TileWidth;

            auto evm = ecs::get_event_manager();
            auto event = evm->get_event<UnitSelected>();
            event->invoke(0);

            std::cout << "Tile clicked " << x_tile << "/" << y_tile << "\n";
            return true;
        }

        it = cm->next<TileMap>();
    }

    auto em = ecs::get_event_manager();
    auto event = em->get_event<TileSelected>();

    return false;
}

bool TileMapRendererSystem::on_mouseup(int x, int y, int button) {
    return false;
}

void TileMapRendererSystem::on_render() {
    auto cm = ecs::get_component_manager();
    auto ent = ecs::get_entity_manager();

    cm->begin<TileMap>();

    auto it = cm->next<TileMap>();
    float tile_start_x = (float)it->TileWidth * -1;
    float tile_start_y = (float)it->TileHeight * -1;

    while(it != nullptr){
        int tiles_per_row = it->TextureWidth / it->TileWidth;
        int tiles_per_col = it->TextureHeight / it->TileHeight;

        auto trans = ent->get_component<Transform2D>(it->Entity);
        if(trans != nullptr){
            glm::vec2 top_corner = world_to_screen(trans->position);

            for(unsigned int x = 0; x < it->Width; x++){

                if(top_corner.x + x * it->TileWidth < tile_start_x)
                    continue;

                if(top_corner.x + x * it->TileWidth > screen_width())
                    continue;

                for(unsigned int y = 0; y < it->Height; y++){

                    if(top_corner.y + y * it->TileHeight < tile_start_y)
                        continue;

                    if(top_corner.y + y * it->TileWidth > screen_height())
                        continue;

                    tile* tile = &it->data[y * it->Height + x];

                    unsigned int tiley = tile->tiletype / tiles_per_row;
                    unsigned int tilex = tile->tiletype - (tiley * tiles_per_row);

                    Rectangle src;
                    Rectangle dst;

                    src.x = tilex * it->TileWidth;
                    src.y = tiley * it->TileHeight;
                    src.width = it->TileWidth;
                    src.height = it->TileHeight;

                    dst.x = top_corner.x + x * it->TileWidth;
                    dst.y = top_corner.y + y * it->TileHeight;
                    dst.width = it->TileWidth;
                    dst.height = it->TileHeight;

                    m_renderer->draw(it->Texture, src, dst);
                }
            }
        }
        it = cm->next<TileMap>();
        break;
    }
}
