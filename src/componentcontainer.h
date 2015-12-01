#ifndef COMPONENT_CONTAINER_H_INCLUDED
#define COMPONENT_CONTAINER_H_INCLUDED

#include <algorithm>
#include "component.h"
#include <vector>

class ComponentContainer
{
protected:
    std::vector<ComponentPtr> components_;

public:
    inline void AddComponent(const ComponentPtr& component)
    {
        if(component->AsAIComponent())
        {
            components_.emplace_back(component);
        }
    }

    inline void RemoveComponent(const ComponentPtr& component)
    {
        components_.erase(
            std::remove(components_.begin(), components_.end(), component),
            components_.end()
        );
    }
};

#endif // COMPONENT_CONTAINER_H_INCLUDED
