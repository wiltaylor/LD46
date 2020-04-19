#ifndef __TILEMAP_RENDERER_SYSTEM_H_
#define __TILEMAP_RENDERER_SYSTEM_H_
#include "ecs/system.h"
#include <functional>
#include "platform/renderer.h"
#include <glm/glm.hpp>

class TileMapRendererSystem : public ecs::System<TileMapRendererSystem> {
public:
    TileMapRendererSystem() {}
    ~TileMapRendererSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;

    void on_render();
    bool on_mousedown(int x, int y, int button);
    bool on_mouseup(int x,int y,int button);

private:
    std::function<void()> m_render_event;
    std::function<bool(int,int,int)> m_mousedown_event;
    std::function<bool(int,int,int)> m_mouseup_event;

    Renderer* m_renderer;
};
#endif // __TILEMAP_RENDERER_SYSTEM_H_
