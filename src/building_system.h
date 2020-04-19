#ifndef LD46_BUILDING_SYSTEM_H
#define LD46_BUILDING_SYSTEM_H
#include "ecs/system.h"
#include "events.h"
#include "components.h"
#include <functional>

class BuildingSystem : public ecs::System<BuildingSystem> {
public:
    BuildingSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_render();
private:
    std::function<void()> m_render_event;
};
#endif //LD46_BUILDING_SYSTEM_H
