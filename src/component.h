#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include "global.h"

class Object;
class AIComponent;
class RenderComponent;

enum ComponentId
{
    AIComponentId,
    RenderComponentId,
    PhysicsComponentId,
    ComponentIdLast
};

class Component
{
    Object* parent_;
public:
    Component();
    virtual ~Component();

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    virtual void Update(uint64_t frame) = 0;

    void SetParent(Object* parent);
    const Object* GetParent() const;
    Object* GetParent();

};

typedef std::shared_ptr<Component> ComponentPtr;
#endif
