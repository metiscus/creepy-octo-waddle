#ifndef COMPONENT_CONTAINER_H_INCLUDED
#define COMPONENT_CONTAINER_H_INCLUDED

#include <algorithm>
#include "component.h"
#include <memory>
#include <vector>

template<typename Base>
class ComponentContainer
{
protected:
    std::vector< std::shared_ptr<Base> > components_;

public:
    inline void AddComponent(const ComponentPtr& component)
    {
        components_.emplace_back(std::shared_ptr<Base>(dynamic_cast<Base*>(component.get())));
    }

    inline void AddComponent(const std::shared_ptr<Base>& component)
    {
        components_.emplace_back(component);
    }

    inline void RemoveComponent(const ComponentPtr& component)
    {
        Base* ptr = std::shared_ptr<Base>(dynamic_cast<Base*>(component.get()));
        components_.erase(
            std::remove(components_.begin(), components_.end(), ptr),
            components_.end()
        );
    }

    inline void RemoveComponent(const std::shared_ptr<Base>& component)
    {
        components_.erase(
            std::remove(components_.begin(), components_.end(), component),
            components_.end()
        );
    }
};

#endif // COMPONENT_CONTAINER_H_INCLUDED
