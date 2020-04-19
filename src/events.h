#ifndef __EVENTS_H_
#define __EVENTS_H_
#include "ecs/event.h"
#include <functional>
#include <vector>
#include <glm/glm.hpp>

void register_all_events();

class StartFrameEvent: public ecs::Event<StartFrameEvent> {
public:
    void register_handler(std::function<void(float)>* handler);
    void unregister_handler(std::function<void(float)>* handler);
    void invoke(float value);


private:
    std::vector<std::function<void(float)>*> m_functions;
};

class StartRenderEvent: public ecs::Event<StartRenderEvent> {
public:
    void register_handler(std::function<void()>* handler);
    void unregister_handler(std::function<void()>* handler);
    void invoke();


private:
    std::vector<std::function<void()>*> m_functions;
};

class RenderEvent: public ecs::Event<RenderEvent> {
public:
    void register_handler(std::function<void()>* handler);
    void unregister_handler(std::function<void()>* handler);
    void invoke();


private:
    std::vector<std::function<void()>*> m_functions;
};

class EndRenderEvent: public ecs::Event<EndRenderEvent> {
public:
    void register_handler(std::function<void()>* handler);
    void unregister_handler(std::function<void()>* handler);
    void invoke();


private:
    std::vector<std::function<void()>*> m_functions;
};

class ShutdownEvent: public ecs::Event<ShutdownEvent> {
public:
    void register_handler(std::function<void()>* handler);
    void unregister_handler(std::function<void()>* handler);
    void invoke();

private:
    std::vector<std::function<void()>*> m_functions;
};

class MouseDownEvent: public ecs::Event<MouseDownEvent> {
public:
    void register_handler(std::function<bool(int,int,int)>* handler);
    void register_handler_priority(std::function<bool(int,int,int)>* handler);
    void unregister_handler(std::function<bool(int,int,int)>* handler);
    void invoke(int x, int y, int button);

private:
    std::vector<std::function<bool(int, int, int)>*> m_functions;
};


class MouseUpEvent: public ecs::Event<MouseUpEvent> {
public:
    void register_handler(std::function<bool(int,int,int)>* handler);
    void register_handler_priority(std::function<bool(int,int,int)>* handler);
    void unregister_handler(std::function<bool(int,int,int)>* handler);
    void invoke(int x, int y, int button);

private:
    std::vector<std::function<bool(int,int,int)>*> m_functions;
};

class TileSelected: public ecs::Event<TileSelected> {
public:
    void register_handler(std::function<void(int, int, int)>* handler);
    void unregister_handler(std::function<void(int, int, int)>* handler);
    void invoke(int x, int y, int button);

private:
    std::vector<std::function<void(int, int, int)>*> m_functions;
};

class UnitSelected: public ecs::Event<UnitSelected> {
public:
    void register_handler(std::function<void(unsigned int)>* handler);
    void unregister_handler(std::function<void(unsigned int)>* handler);
    void invoke(unsigned int entity);

private:
    std::vector<std::function<void(unsigned int)>*> m_functions;
};


class UnitTargeted: public ecs::Event<UnitTargeted> {
public:
    void register_handler(std::function<void(unsigned int)>* handler);
    void unregister_handler(std::function<void(unsigned int)>* handler);
    void invoke(unsigned int entity);

private:
    std::vector<std::function<void(unsigned int)>*> m_functions;
};
#endif // __EVENTS_H_
