#ifndef __RENDERER_H_
#define __RENDERER_H_
#include <glm/glm.hpp>

class Renderer {
public:
    Renderer() {};
    virtual ~Renderer() {};

    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void draw(unsigned int resource_id, glm::vec2 position) = 0;
    virtual void draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect) = 0;
    virtual void draw(unsigned int resource_id, glm::mat2 srcRect, glm::mat2 destRect, glm::vec2 center, float angle) = 0;
};

Renderer* get_renderer();

#endif // __RENDERER_H_
