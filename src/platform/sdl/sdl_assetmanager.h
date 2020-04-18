#ifndef __SDL_ASSETMANAGER_H_
#define __SDL_ASSETMANAGER_H_
#include "../asset.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <glm/fwd.hpp>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>

struct SDLTexture {
    SDL_Texture* raw;
    AssetPersistance presistance;
    int width;
    int height;
    Uint32 format;
    int access;
};

class SDLAssetManager: public AssetManager {
public:
    SDLAssetManager(SDL_Renderer* renderer);
    ~SDLAssetManager() override;

    unsigned int get_texture_asset(const char*name, AssetPersistance persist) override;

    SDLTexture* get_texture(unsigned int id);

private:
    unsigned int next_id = 0;
    std::unordered_map<const char*, unsigned int> m_idlookup;
    std::unordered_map<unsigned int, SDLTexture> m_textures;
    SDL_Renderer* m_renderer;
    std::function<void()> m_shutdown;
};


#endif // __SDL_ASSETMANAGER_H_
