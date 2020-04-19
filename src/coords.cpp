//
// Created by wil on 19/4/20.
//
#include "coords.h"
#include "ecs/component.h"
#include "components.h"
#include <assert.h>

glm::vec2 world_to_screen(const glm::vec2& position){
    auto cm = ecs::get_component_manager();
    cm->begin<Camera2D>();
    auto cam = cm->next<Camera2D>();

    assert(cam != nullptr);

    return glm::vec2(position.x - cam->position.x, position.y - cam->position.y);
}

glm::vec2 screen_to_world(const glm::vec2& position){
    auto cm = ecs::get_component_manager();
    cm->begin<Camera2D>();
    auto cam = cm->next<Camera2D>();

    assert(cam != nullptr);

    return glm::vec2(position.x + cam->position.x, position.y + cam->position.y);
}


glm::vec2 world_to_local(const glm::vec2& position, const glm::vec2& parent){
    return glm::vec2(position.x + parent.x, position.y + parent.y);
}

float screen_width(){ return 900.0f;}
float screen_height(){ return 600.0f;}
