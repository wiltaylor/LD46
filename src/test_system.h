#ifndef __TEST_SYSTEM_H_
#define __TEST_SYSTEM_H_
#include "ecs/system.h"
#include "events.h"

class TestSystem: public ecs::System<TestSystem> {
public:
    TestSystem() {}
    ~TestSystem() {}

    void init() override;
    void on_enable() override;
    void on_disable() override;
private:
    std::function<void(float)> m_on_update;
};


#endif // __TEST_SYSTEM_H_
