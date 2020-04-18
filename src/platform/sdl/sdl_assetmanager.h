#ifndef __SDL_ASSETMANAGER_H_
#define __SDL_ASSETMANAGER_H_
#include "../asset.h"
#include <SDL2/SDL_render.h>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>

struct SDLTexture {
    SDL_Texture* raw;
    AssetPersistance presistance;
};

class SDLAssetManager: public AssetManager {
public:
    SDLAssetManager(SDL_Renderer* renderer);
    ~SDLAssetManager() override;

    unsigned int get_texture_asset(char*name, AssetPersistance persist) override;

private:
    unsigned int next_id = 0;
    std::unordered_map<char*, unsigned int> m_idlookup;
    std::unordered_map<unsigned int, SDLTexture> m_textures;
    SDL_Renderer* m_renderer;
    std::function<void()> m_shutdown;
};


#endif // __SDL_ASSETMANAGER_H_
