#include "events.h"
#include <algorithm>
#include "platform/log.h"

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

void RenderEvent::register_handler(std::function<void()>* handler) {
    m_functions.push_back(handler);
}

void RenderEvent::unregister_handler(std::function<void() >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void RenderEvent::invoke(){

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

void MouseDownEvent::register_handler(std::function<bool(int,int,int)>* handler) {
    m_functions.push_back(handler);
}

void MouseDownEvent::register_handler_priority(std::function<bool(int,int,int)>* handler){
    m_functions.insert(m_functions.begin(), handler);
}

void MouseDownEvent::unregister_handler(std::function<bool(int,int,int) >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void MouseDownEvent::invoke(int x, int y, int button){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        if(func(x, y, button))
            return; //If handled don't process rest.
    }
}

void MouseUpEvent::register_handler(std::function<bool(int, int, int)>* handler) {
m_functions.push_back(handler);
}

void MouseUpEvent::register_handler_priority(std::function<bool(int,int,int)>* handler){
    m_functions.insert(m_functions.begin(), handler);
}

void MouseUpEvent::unregister_handler(std::function<bool(int, int, int) >* handler){
m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void MouseUpEvent::invoke(int x, int y, int button){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        if(func(x, y, button))
            return; //If handled don't process rest.
    }
}

void TileSelected::register_handler(std::function<void(unsigned int, int,int,int)>* handler) {
    m_functions.push_back(handler);
}

void TileSelected::unregister_handler(std::function<void(unsigned int, int,int,int) >* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void TileSelected::invoke(unsigned int tilemap, int x, int y, int button){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(tilemap, x, y, button);
    }
}

void UnitSelected::register_handler(std::function<void(unsigned int)>* handler) {
    m_functions.push_back(handler);
}

void UnitSelected::unregister_handler(std::function<void(unsigned int)>* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void UnitSelected::invoke(unsigned int entity){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(entity);
    }
}

void UnitTargeted::register_handler(std::function<void(unsigned int)>* handler) {
m_functions.push_back(handler);
}

void UnitTargeted::unregister_handler(std::function<void(unsigned int)>* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void UnitTargeted::invoke(unsigned int entity){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(entity);
    }
}

void SpawnUnitEvent::register_handler(std::function<void(UnitType, float, float)>* handler) {
    m_functions.push_back(handler);
}

void SpawnUnitEvent::unregister_handler(std::function<void(UnitType, float, float)>* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void SpawnUnitEvent::invoke(UnitType type, float x, float y){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(type, x, y);
    }
}

void SpawnBuildingEvent::register_handler(std::function<void(BuildingType, float, float)>* handler) {
    m_functions.push_back(handler);
}

void SpawnBuildingEvent::unregister_handler(std::function<void(BuildingType, float, float)>* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void SpawnBuildingEvent::invoke(BuildingType type, float x, float y){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(type, x, y);
    }
}

void LoadLevelEvent::register_handler(std::function<void(unsigned int)>* handler) {
    m_functions.push_back(handler);
}

void LoadLevelEvent::unregister_handler(std::function<void(unsigned int)>* handler){
    m_functions.erase(std::remove(m_functions.begin(), m_functions.end(), handler), m_functions.end());
}

void LoadLevelEvent::invoke(unsigned int index){

    for(auto i = 0; i < m_functions.size(); i++){
        auto func = *m_functions[i];

        func(index);
    }
}
