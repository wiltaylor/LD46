#include "sdl_assetmanager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include "sdl_renderer.h"
#include "../../events.h"
#include "../log.h"

static SDLAssetManager* current_instance = nullptr;


AssetManager* get_asset_manager(){
    if(current_instance == nullptr){

        auto rend = reinterpret_cast<SDLRenderer*>(get_renderer());
        current_instance = new SDLAssetManager(rend->m_renderer);
    }

    return current_instance;
}

unsigned int SDLAssetManager::get_texture_asset(const char* name, AssetPersistance persist) {
    auto it = m_idlookup.find(name);

    if(it == m_idlookup.end()){
        log_info("Loading file from disk!");

        auto id = next_id++;
        SDLTexture new_text{IMG_LoadTexture(m_renderer, name), persist, 0, 0, 0, 0};

        SDL_QueryTexture(new_text.raw, &new_text.format, &new_text.access, &new_text.width, &new_text.height);

        m_idlookup.insert(std::pair<const char*, unsigned int>(name, id));
        m_textures.insert(std::pair<unsigned int, SDLTexture>(id, new_text));

        return id;
    }else{
        return it->second;
    }
}

SDLAssetManager::SDLAssetManager(SDL_Renderer* renderer): m_renderer{renderer} {
    IMG_Init(IMG_INIT_PNG);
}

SDLAssetManager::~SDLAssetManager() {
    IMG_Quit();
}

SDLTexture* SDLAssetManager::get_texture(unsigned int id){
    auto it = m_textures.find(id) ;

    if(it == m_textures.end())
        return nullptr;

    return &it->second;
}
