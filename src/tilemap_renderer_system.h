#ifndef __TILEMAP_RENDERER_SYSTEM_H_
#define __TILEMAP_RENDERER_SYSTEM_H_
#include "ecs/system.h"
#include <functional>
#include "platform/renderer.h"

class TileMapRendererSystem : public ecs::System<TileMapRendererSystem> {
public:
    TileMapRendererSystem() {}
    ~TileMapRendererSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;

    void on_render();

private:
    std::function<void()> m_render_event;
    Renderer* m_renderer;
};


#endif // __TILEMAP_RENDERER_SYSTEM_H_
