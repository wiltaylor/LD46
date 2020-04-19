#include "../../application.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    Application app;

    float now = SDL_GetPerformanceCounter();
    float last = 0.0f;
    float delta_time = 0.0f;

    while(app.onTick(delta_time)){

        last = now;
        now = SDL_GetPerformanceCounter();
        delta_time = (now - last) / (float)SDL_GetPerformanceFrequency();
    }
}
