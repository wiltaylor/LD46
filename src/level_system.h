#ifndef LD46_LEVEL_SYSTEM_H
#define LD46_LEVEL_SYSTEM_H
#include "ecs/system.h"
#include "events.h"
#include <functional>

class LevelSystem: public ecs::System<LevelSystem> {
public:
    LevelSystem(){}

    void init() override;
    void on_enable() override;
    void on_disable() override;
    void on_load_level(unsigned int index);

private:

    void clear_level();
    void build_camera();
    void new_tilemap(int width, int height, unsigned int default_tile);

    std::function<void(unsigned int)> m_load_level_event;

    unsigned int m_tilemap_texture;
};

#endif //LD46_LEVEL_SYSTEM_H
