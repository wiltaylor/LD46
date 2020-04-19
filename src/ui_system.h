#ifndef LD46_UI_SYSTEM_H
#define LD46_UI_SYSTEM_H
#include "ecs/system.h"
#include "events.h"
#include "components.h"
#include <functional>
#include "platform/renderer.h"

class UISystem: public ecs::System<UISystem>{
public:
    UISystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_render();

private:
    std::function<void()> m_render_event;
    unsigned int m_ui_sprite;
    unsigned int m_emptybar_sprite;
    unsigned int m_font;
};
#endif //LD46_UI_SYSTEM_H
