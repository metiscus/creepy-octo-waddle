#ifndef AIWORLD_H_INCLUDED
#define AIWORLD_H_INCLUDED

#include "aicomponent.h"
#include "component.h"
#include "vector.h"
#include "componentcontainer.h"

#include <vector>

class AIWorld : public ComponentContainer<AIComponent>
{
public:
    AIWorld() = default;
    ~AIWorld() = default;

    std::vector<ComponentPtr> QueryRange(const Vector2& center, float range);

};




#endif
