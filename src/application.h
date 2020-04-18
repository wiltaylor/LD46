#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#include "events.h"
#include <functional>

class Application {
public:
    Application();
    ~Application();

    bool onTick(float deltaTime);
    void onExit();
private:
    StartFrameEvent* m_startFrame;
    StartRenderEvent* m_startRender;
    EndRenderEvent* m_endRender;
    ShutdownEvent* m_shutdown;
    bool m_running = true;

    std::function<void()> m_exitHandler;
};


#endif // __APPLICATION_H_
