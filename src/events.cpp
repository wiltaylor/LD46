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

void StartRenderEvent::register_handler(std::function<void()>* handler) {
    m_functions.push_back(handler);
}

void StartRenderEvent::unregister_handler(std::function<void() >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void StartRenderEvent::invoke(){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func();
    }

}

void EndRenderEvent::register_handler(std::function<void()>* handler) {
    m_functions.push_back(handler);
}

void EndRenderEvent::unregister_handler(std::function<void() >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void EndRenderEvent::invoke(){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func();
    }

}

void ShutdownEvent::register_handler(std::function<void()>* handler) {
    m_functions.push_back(handler);
}

void ShutdownEvent::unregister_handler(std::function<void() >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void ShutdownEvent::invoke(){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func();
    }

}
