#ifndef __ENTITY_H_
#define __ENTITY_H_
#include "component.h"
#include <unordered_map>
#include <vector>
#include <iostream>

namespace ecs{
    struct GenerativeIndex;


    class EntityManager {
    public:
        EntityManager(){};
        ~EntityManager();

        bool entity_exists(unsigned int entity);
        unsigned int add_entity();
        void remove_entity(unsigned int entity);
        void add_tag(unsigned int entity, unsigned int tagId);
        void remove_tag(unsigned int entity, unsigned int tagId);
        const std::vector<unsigned int>* get_tags(unsigned int entity);

        void clear_all();

        template<typename T>
        T* add_component(unsigned int entity) {
            if(!entity_exists(entity))
                return nullptr;

            auto cm = get_component_manager();
            auto index = cm->add_component<T>(entity);

            m_components[entity]->push_back(index);

            return cm->get_component<T>(index);
        }

        template<typename T>
        T* get_component(unsigned int entity){
            auto index = this->get_component_index<T>(entity);

            if(index == nullptr)
                return nullptr;
            auto cm = get_component_manager();

            return cm->get_component<T>(*index);
        }

        template<typename T>
        GenerativeIndex* get_component_index(unsigned int entity){
            auto it = m_components.find(entity);

            if(it == m_components.end())
                return nullptr;

            auto vec = it->second;

            for(auto i = 0; i < it->second->size(); i++){
                if(vec->at(i).type_id == T::TypeId){

                    return &vec->at(i);
                }
            }

            return nullptr;
        }

            friend class ComponentContainer;

    private:
        unsigned int m_next_entity_id = 0;
        std::unordered_map<unsigned int, std::vector<GenerativeIndex>*> m_components;
        std::unordered_map<unsigned int, std::vector<unsigned int>*> m_tags;
    };

    EntityManager* get_entity_manager();
}
#endif
