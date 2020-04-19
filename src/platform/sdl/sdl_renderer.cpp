#include "sdl_renderer.h"
#include "../log.h"
#include <cstdlib>
#include <iostream>

static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;
static SDLRenderer* current_renderer = nullptr;

Renderer* get_renderer() {
    if(current_renderer == nullptr)
        current_renderer = new SDLRenderer();

    return current_renderer;
}


SDLRenderer::SDLRenderer() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_fatal("Failed to start SDL!");

        std::abort();
    }

    if(TTF_Init() < 0)
    {
        log_fatal("Failed to load SDL TTF!");
        std::abort();
    }

    m_window = SDL_CreateWindow("LD46", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(m_window == nullptr) {
        log_fatal("Failed to create SDL window!");

        std::abort();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);


}

SDLRenderer::~SDLRenderer() {
   TTF_Quit();
   SDL_Quit();
}

void SDLRenderer::begin(){
    SDL_RenderClear(m_renderer);
}

void SDLRenderer::end(){
    SDL_RenderPresent(m_renderer);
}

void SDLRenderer::draw(unsigned int resource_id, glm::vec2 position) {

    if(m_assetman == nullptr)
        m_assetman = reinterpret_cast<SDLAssetManager*>(get_asset_manager());

    auto text = m_assetman->get_texture(resource_id);

    SDL_Rect dest;

    dest.x = position.x;
    dest.y = position.y;
    dest.w = text->width;
    dest.h = text->height;

    SDL_RenderCopy(m_renderer, text->raw, nullptr, &dest);
}

void SDLRenderer::draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect) {

    if(m_assetman == nullptr)
        m_assetman = reinterpret_cast<SDLAssetManager*>(get_asset_manager());

    auto text = m_assetman->get_texture(resource_id);

    SDL_Rect src;
    SDL_Rect dest;

    src.x = srcRect.x;
    src.y = srcRect.y;
    src.w = srcRect.width;
    src.h = srcRect.height;

    dest.x = destRect.x;
    dest.y = destRect.y;
    dest.w = destRect.width;
    dest.h = destRect.height;

    SDL_RenderCopy(m_renderer, text->raw, &src, &dest);
}

void SDLRenderer::draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect, glm::vec2 center, float angle) {
   
}

void SDLRenderer::draw_text(unsigned int font_id, const char* text, glm::vec2 position){

    if(m_assetman == nullptr)
        m_assetman = reinterpret_cast<SDLAssetManager*>(get_asset_manager());

    auto font = m_assetman->get_font(font_id);
    SDL_Rect dest;

    dest.x = position.x;
    dest.y = position.y;
    dest.w = 0;
    dest.h = 0;
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font->raw, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

    SDL_RenderCopy(m_renderer, texture, nullptr, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}