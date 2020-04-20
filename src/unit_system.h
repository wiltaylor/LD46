#ifndef LD46_UNIT_SYSTEM_H
#define LD46_UNIT_SYSTEM_H
#include "ecs/system.h"
#include "events.h"
#include "components.h"
#include <functional>

class UnitSystem: public ecs::System<UnitSystem> {
public:
    UnitSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_render();
    void on_update(float delta_time);

    bool on_mousedown(int x, int y, int button);
    bool on_mouseup(int x, int y, int button);
    void on_targeted(unsigned int entity);
    void on_selected(unsigned int entity);
    void on_spawn(UnitType type, float x, float y);
    void on_tile_selected(unsigned int, int x, int y, int button);

private:
    std::function<void()> m_render_event;
    std::function<void(float)> m_update_event;

    std::function<bool(int,int,int)> m_mousedown_event;
    std::function<bool(int,int,int)> m_mouseup_event;
    std::function<void(unsigned int)> m_targeted_event;
    std::function<void(unsigned int)> m_selected_event;
    std::function<void(UnitType, float, float)> m_spawn_event;
    std::function<void(unsigned int, int,int,int)> m_tile_selected_event;

    unsigned int m_worker_down_id;
    unsigned int m_worker_up_id;
    unsigned int m_worker_left_id;
    unsigned int m_worker_right_id;

    unsigned int m_wizard_down_id;
    unsigned int m_wizard_up_id;
    unsigned int m_wizard_left_id;
    unsigned int m_wizard_right_id;


    unsigned int m_badguy_down_id;
    unsigned int m_badguy_up_id;
    unsigned int m_badguy_left_id;
    unsigned int m_badguy_right_id;

    unsigned int m_selected_unit = 0;
};
#endif //LD46_UNIT_SYSTEM_H
