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

    bool on_mousedown(int x, int y, int button);
    bool on_mouseup(int x, int y, int button);


private:
    std::function<void()> m_render_event;


    std::function<bool(int,int,int)> m_mousedown_event;
    std::function<bool(int,int,int)> m_mouseup_event;
};
#endif //LD46_BUILDING_SYSTEM_H
