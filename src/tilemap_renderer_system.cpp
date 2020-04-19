#include "tilemap_renderer_system.h"
#include "events.h"
#include "components.h"
#include "ecs/entity.h"
#include <iostream>
#include <glm/glm.hpp>
#include "tilemap.h"

void TileMapRendererSystem::init(){
    m_render_event = std::bind(&TileMapRendererSystem::on_render, this);
    m_renderer = get_renderer();

    std::cout << "loaded tilemap renderer\n";
}

void TileMapRendererSystem::on_enable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->register_handler(&m_render_event);
   
}

void TileMapRendererSystem::on_disable(){
    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->unregister_handler(&m_render_event);
}

void TileMapRendererSystem::on_render() {
    auto cm = ecs::get_component_manager();
    auto ent = ecs::get_entity_manager();

    cm->begin<TileMap>();

    auto it = cm->next<TileMap>();

    while(it != nullptr){
        auto transformid = ent->get_component<Transform2D>(it->Entity);

        int tiles_per_row = it->TextureWidth / it->TileWidth;
        int tiles_per_col = it->TextureHeight / it->TileHeight;

        if(transformid != nullptr){
            auto trans = cm->get_component<Transform2D>(*transformid);

            std::cout << "bang1\n";
            for(unsigned int x = 0; x < it->Width; x++){
                for(unsigned int y = 0; y < it->Height; y++){
                    std::cout << "bang bang\n";


                    tile* tile = &it->data[y * it->Height + x];

                    unsigned int tiley = tile->tiletype / tiles_per_row;
                    unsigned int tilex = tile->tiletype - (tiley * tiles_per_row);

                    Rectangle src;
                    Rectangle dst;

                    src.x = tilex * it->TileWidth;
                    src.y = tiley * it->TileHeight;
                    src.width = it->TileWidth;
                    src.height = it->TileHeight;

                    dst.x = trans->position.x + x * it->TileWidth;
                    dst.y = trans->position.y + y * it->TileHeight;
                    dst.width = it->TileWidth;
                    dst.height = it->TileHeight;

                    m_renderer->draw(it->Texture, src, dst);
                }
            }

//            m_renderer->draw(it->Texture, trans->position);
        }
        it = cm->next<TileMap>();
        break;
    }
}
