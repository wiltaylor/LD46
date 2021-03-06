#ifndef __RENDERER_H_
#define __RENDERER_H_
#include <glm/glm.hpp>

struct Rectangle{
    float x;
    float y;
    float width;
    float height;
};

class Renderer {
public:
    Renderer() {};
    virtual ~Renderer() {};

    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void draw(unsigned int resource_id, glm::vec2 position) = 0;
    virtual void draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect) = 0;
    virtual void draw(unsigned int resource_id, Rectangle srcRect, Rectangle destRect, glm::vec2 center, float angle) = 0;
    virtual void draw_text(unsigned int font_id, const char* text, glm::vec2 position) = 0;
};

Renderer* get_renderer();

#endif // __RENDERER_H_
