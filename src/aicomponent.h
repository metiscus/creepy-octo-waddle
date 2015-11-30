#ifndef AICOMPONENT_H_INCLUDED
#define AICOMPONENT_H_INCLUDED

#include "component.h"
#include <memory>

class AIWorld;

class AIComponent : public Component
{
    AIWorld* world_;
public:
    AIComponent();
    virtual ~AIComponent() = default;

    void SetWorld(AIWorld* world);

    virtual void Update(uint64_t frame);
};

#endif 
