#ifndef __RENDER_SYSTEM_H_
#define __RENDER_SYSTEM_H_
#include "ecs/system.h"
#include "ecs/event.h"
#include <functional>
#include "platform/renderer.h"

class RenderSystem: public ecs::System<RenderSystem>{
public:
    RenderSystem() {};

    void init() override;
    void on_enable() override;
    void on_disable() override;

    void on_start();
    void on_end();

private:
    std::function<void()> m_startrender;
    std::function<void()> m_endrender;
    Renderer* m_renderer;
};


#endif // __RENDER_SYSTEM_H_
