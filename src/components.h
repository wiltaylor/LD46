#ifndef __COMPONENTS_H_
#define __COMPONENTS_H_
#include "ecs/component.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "tilemap.h"
#include <vector>

struct Transform2D: public ecs::Component<Transform2D>{
    glm::vec2 position;
    float rotation;
};

struct SpriteRenderer: public ecs::Component<SpriteRenderer>{
    unsigned int AssetId;
};

 struct Camera2D: public ecs::Component<Camera2D> {
    glm::vec2 position;
    float width;
    float height;
    float scroll_speed;
    glm::vec2 max_position;
    glm::vec2 min_position;
};

struct TileMap: public ecs::Component<TileMap> {
    unsigned int Texture;
    unsigned int TileWidth;
    unsigned int TileHeight;
    unsigned int TextureWidth;
    unsigned int TextureHeight;
    int Width;
    int Height;
    std::vector<tile> data;
};

enum BuildingType{
    BUILDING_Monster,
    BUILDING_Burger
};

struct Building: public ecs::Component<Building> {
    std::vector<unsigned int> animation_frames;
    float hp;
    float max_hp;
    float hp_recovery;
    float animation_speed;
    float time_to_next_frame;
    unsigned int current_frame;
    int width;
    int height;
    BuildingType type;
};

enum UnitDirection{
    UNIT_UP,
    UNIT_DOWN,
    UNIT_LEFT,
    UNIT_RIGHT
};

enum UnitType{
    UNIT_Cultist,
    UNIT_Wizard,
    UNIT_Enemy
};

struct Unit: public ecs::Component<Unit> {
    unsigned int up_texture;
    unsigned int down_texture;
    unsigned int left_texture;
    unsigned int right_texture;
    UnitDirection direction;
    int width;
    int height;
    float speed;
    UnitType type;
    bool hide;
};

enum AIState {
    AI_IDLE,
    AI_MOVE,
    AI_GATHER,
    AI_RETURN,
    AI_WAITING_ON_ORDER
};

struct UnitAI : public ecs::Component<UnitAI> {
    glm::vec2 target;
    AIState state;
    float hide_timeout;
    float current_hide;
    unsigned int harvest_entity;
};

struct Collider: public ecs::Component<Collider> {
    float radius;
};

#endif // __COMPONENTS_H_
