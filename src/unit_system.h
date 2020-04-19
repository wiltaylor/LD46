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

private:
    std::function<void()> m_render_event;
    std::function<void(float)> m_update_event;
};
#endif //LD46_UNIT_SYSTEM_H
