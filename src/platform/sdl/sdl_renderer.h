#ifndef __SDL_RENDERER_H_
#define __SDL_RENDERER_H_
#include <SDL2/SDL.h>
#include "../renderer.h"
#include <functional>
#include "sdl_assetmanager.h"

class AssetManager;

class SDLRenderer: public Renderer{
public:
    SDLRenderer();
    ~SDLRenderer() override;

    void begin() override;
    void end() override;
    void draw(unsigned int resource_id, glm::vec2 position) override;
    void draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect) override;
    void draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect, glm::vec2 center, float angle) override;

friend AssetManager* get_asset_manager();

private:
    SDL_Window* m_window;
    SDL_Renderer *m_renderer;
    std::function<void()> m_shutdown;
    SDLAssetManager* m_assetman;
};


#endif // __SDL_RENDERER_H_
