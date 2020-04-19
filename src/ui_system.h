#ifndef LD46_UI_SYSTEM_H
#define LD46_UI_SYSTEM_H
#include "ecs/system.h"
#include "events.h"
#include "components.h"
#include <functional>
#include "platform/renderer.h"

enum BarColor {
    BAR_Red,
    BAR_Green,
    BAR_Power
};

class UISystem: public ecs::System<UISystem>{
public:
    UISystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_render();

    bool on_mousedown(int x, int y, int button);
    bool on_mouseup(int x, int y, int button);
    void on_unit_select(unsigned int entity);

private:
    void render_bar(float x, float y, const char* text, float percent, BarColor color);

    std::function<void()> m_render_event;
    std::function<bool(int,int,int)> m_mousedown_event;
    std::function<bool(int,int,int)> m_mouseup_event;
    std::function<void(unsigned int)> m_unit_select_event;

    unsigned int m_ui_sprite;
    unsigned int m_ui_bar_empty;
    unsigned int m_ui_bar_red;
    unsigned int m_ui_bar_green;
    unsigned int m_ui_bar_power;
    unsigned int m_font;
    unsigned int m_selected_entity;
};
#endif //LD46_UI_SYSTEM_H
