#ifndef __COMPONENTS_H_
#define __COMPONENTS_H_
#include "ecs/component.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

struct Transform2D: public ecs::Component<Transform2D>{
    glm::vec2 position;
    float rotation;
};

struct SpriteRenderer: public ecs::Component<SpriteRenderer>{
    unsigned int AssetId;
};

struct Camera2D: public ecs::Component<Camera2D> {
    glm::mat2 boundingbox;
};


#endif // __COMPONENTS_H_
