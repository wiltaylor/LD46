#ifndef __SDL_RENDERER_H_
#define __SDL_RENDERER_H_
#include <SDL2/SDL.h>
#include "../renderer.h"

class SDLRenderer: public Renderer{
public:
    SDLRenderer();
    ~SDLRenderer() override;

    void begin() override;
    void end() override;
    void draw(unsigned int resource_id, glm::vec2 position) override;
    void draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect) override;
    void draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect, glm::vec2 center, float angle) override;



private:
    SDL_Window* m_window;
    SDL_Renderer *m_renderer;

};


#endif // __SDL_RENDERER_H_
