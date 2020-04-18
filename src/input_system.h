#ifndef __INPUT_SYSTEM_H_
#define __INPUT_SYSTEM_H_
#include "ecs/system.h"
#include <functional>
#include <SDL2/SDL.h>

class InputSystem: public ecs::System<InputSystem> {
public:
    InputSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_update(float);
private:

    std::function<void(float)> m_startframe;
    SDL_Event m_event;
};


#endif // __INPUT_SYSTEM_H_
