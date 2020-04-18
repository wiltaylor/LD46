#ifndef __SPRITE_RENDER_SYSTEM_H_
#define __SPRITE_RENDER_SYSTEM_H_
#include "ecs/system.h"
#include <functional>
#include "platform/renderer.h"

class SpriteRenderSystem: public ecs::System<SpriteRenderSystem> {
public:
    SpriteRenderSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_render();

private:
    std::function<void()> m_renderhandler;
    Renderer* m_renderer;
};


#endif // __SPRITE_RENDER_SYSTEM_H_
