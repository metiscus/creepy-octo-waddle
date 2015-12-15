#ifndef AIWORLD_H_INCLUDED
#define AIWORLD_H_INCLUDED

#include "global.h"
#include "aicomponent.h"
#include "component.h"
#include "vector.h"
#include "componentcontainer.h"

class AIWorld : public ComponentContainer<AIComponent>
{
public:
    AIWorld() = default;
    ~AIWorld() = default;

    std::vector<ComponentPtr> QueryRange(const Vector& center, float range);

};




#endif
