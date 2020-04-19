//
// Created by wil on 19/4/20.
//
#ifndef LD46_COORDS_H
#define LD46_COORDS_H
#include <glm/glm.hpp>

glm::vec2 world_to_screen(const glm::vec2& position);
glm::vec2 screen_to_world(const glm::vec2& position);
glm::vec2 world_to_local(const glm::vec2& position, const glm::vec2& parent);

float screen_width();
float screen_height();

#endif //LD46_COORDS_H
