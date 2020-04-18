#ifndef __EVENTS_H_
#define __EVENTS_H_
#include "ecs/event.h"
#include <functional>
#include <vector>

class StartFrameEvent: public ecs::Event<StartFrameEvent> {
public:
    void register_handler(std::function<void(float)>* handler);
    void unregister_handler(std::function<void(float)>* handler);
    void invoke(float value);


private:
    std::vector<std::function<void(float)>*> m_functions;
};


#endif // __EVENTS_H_
