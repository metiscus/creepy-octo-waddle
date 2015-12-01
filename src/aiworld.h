#ifndef AIWORLD_H_INCLUDED
#define AIWORLD_H_INCLUDED

#include "aicomponent.h"
#include "component.h"
#include "vector.h"

#include <vector>

class AIWorld
{
private:
    std::vector<ComponentPtr> components_;
    
public:
    AIWorld() = default;
    ~AIWorld() = default;

    std::vector<ComponentPtr> QueryRange(const Vector2& center, float range);
    void AddComponent(const ComponentPtr& component);
    void RemoveComponent(const ComponentPtr& component);

};




#endif 
