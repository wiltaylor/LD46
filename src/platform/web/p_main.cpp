#include <iostream>
#include <emscripten.h>
#include "../log.h"
#include "../../application.h"
#include <SDL2/SDL.h>

float now = SDL_GetPerformanceCounter();
float last = 0.0f;
float delta_time = 0.0f;
Application app;

void main_loop() {
    last = now;

    now = SDL_GetPerformanceCounter();
    delta_time = (now - last)  / (float)SDL_GetPerformanceFrequency();

    app.onTick(delta_time);

}


int main() {
    emscripten_set_main_loop(main_loop, 0, 1);
}
