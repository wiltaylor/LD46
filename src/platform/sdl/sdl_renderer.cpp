#include "sdl_renderer.h"
#include "../log.h"
#include <cstdlib>

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

    m_window = SDL_CreateWindow("LD46", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(m_window == nullptr) {
        log_fatal("Failed to create SDL window!");

        std::abort();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

SDLRenderer::~SDLRenderer() {
   
}

void SDLRenderer::begin(){
    SDL_RenderClear(m_renderer);
}

void SDLRenderer::end(){
    SDL_RenderPresent(m_renderer);
}

void SDLRenderer::draw(unsigned int resource_id, glm::vec2 position) {
    //SDL_RenderCopy(m_renderer, resource_id, {}, {});
}

void SDLRenderer::draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect) {

}

void SDLRenderer::draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect, glm::vec2 center, float angle) {
   
}
