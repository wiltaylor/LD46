#include "events.h"
#include <algorithm>
void StartFrameEvent::register_handler(std::function<void(float)>* handler) {
    m_functions.push_back(handler);
}

void StartFrameEvent::unregister_handler(std::function<void(float) >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void StartFrameEvent::invoke(float value){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(value);
    }

}
