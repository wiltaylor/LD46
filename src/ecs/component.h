#ifndef __COMPONENT_H_
#define __COMPONENT_H_
#include <cstddef>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace ecs {

    class EntityManager;
    EntityManager* get_entity_manager();

    struct ComponentBase {
        unsigned int Entity;
        static unsigned int nextID();
    };

    template<typename T>
    struct Component : public ComponentBase {
        static const unsigned int TypeId;
        static const size_t SizeInBytes;
    };

    template<typename T>
    const unsigned int Component<T>::TypeId(ComponentBase::nextID());

    template<typename T>
    const size_t Component<T>::SizeInBytes(sizeof(T));


    struct GenerativeIndex {
        size_t ordinal;
        size_t generation;
        unsigned int type_id;
    };

    class ComponentContainer {
    public:
        ComponentContainer(size_t capacity, size_t item_size, unsigned int type_id);
        ~ComponentContainer();
        char* get_component(GenerativeIndex& index);
        void remove_component(GenerativeIndex& index);
        GenerativeIndex add_component(unsigned int entity);
        size_t item_size() { return m_item_size; }
        void begin();
        char* next();

    private:
        std::vector<bool> m_inuse;
        std::vector<size_t> m_generation;
        size_t m_item_size;
        size_t m_capacity;
        char* m_data;
        size_t m_current_ordinal;
        unsigned int m_type_id;
    };

    class ComponentManager {
    public:
        ComponentManager(){}
        ~ComponentManager();

        template<typename T>
        void register_component_type(size_t capacity){
            m_component_storage.insert(std::pair<unsigned int, ecs::ComponentContainer*>(T::TypeId, new ecs::ComponentContainer(capacity, T::SizeInBytes, T::TypeId)));
        }

        template<typename T>
        T* get_component(GenerativeIndex& index) {
            assert(T::TypeId == index.type_id);
            return reinterpret_cast<T*>(m_component_storage[index.type_id]->get_component(index));
        }

        //Not for calling directly
        template<typename T>
        GenerativeIndex add_component(unsigned int entity) {
            auto result = m_component_storage[T::TypeId]->add_component(entity);
            return result;
        }

        void remove_component(GenerativeIndex& index);

        template<typename T>
        void begin() {
            m_component_storage[T::TypeId]->begin();
        }

        template<typename T>
        T* next(){
            return reinterpret_cast<T*>(m_component_storage[T::TypeId]->next());
        }


    private:
        std::unordered_map<unsigned int, ecs::ComponentContainer*> m_component_storage;
    };


    ecs::ComponentManager* get_component_manager();
}
#endif
