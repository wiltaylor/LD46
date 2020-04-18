#ifndef __EVENTS_H_
#define __EVENTS_H_
#include "ecs/event.h"
#include <functional>
#include <vector>

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

#endif // __EVENTS_H_
