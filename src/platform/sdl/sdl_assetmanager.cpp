#include "sdl_assetmanager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include "sdl_renderer.h"
#include "../../events.h"

static SDLAssetManager* current_instance = nullptr;


AssetManager* get_assetmanager(){
    if(current_instance == nullptr){

        auto rend = reinterpret_cast<SDLRenderer*>(get_renderer());
        current_instance = new SDLAssetManager(rend->m_renderer);
    }

    return current_instance;
}

unsigned int SDLAssetManager::get_texture_asset(char* name, AssetPersistance persist) {
    auto it = m_idlookup.find(name);

    if(it == m_idlookup.end()){
        auto id = next_id++;
        SDLTexture new_text{IMG_LoadTexture(m_renderer, name), persist};

        m_idlookup.insert(std::pair<char*, unsigned int>(name, id));
        m_textures.insert(std::pair<unsigned int, SDLTexture>(id, new_text));

        return id;
    }else{
        return it->second;
    }
}

SDLAssetManager::SDLAssetManager(SDL_Renderer* renderer): m_renderer{renderer} {
    IMG_Init(IMG_INIT_PNG);
    m_shutdown = [](){
        if(current_instance != nullptr)
            delete current_instance;
        current_instance = nullptr;;
    };

    auto em = ecs::get_event_manager();
    auto shutdown_event = em->get_event<ShutdownEvent>();

    shutdown_event->register_handler(&m_shutdown);
}

SDLAssetManager::~SDLAssetManager() {
    IMG_Quit();
}
