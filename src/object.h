#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <array>
#include "component.h"
#include <memory>
#include "vector.h"

enum ComponentId
{
    AIComponentId,
    ComponentIdLast
};

class Object
{
public:
    Object();
    ~Object();

    void SetComponent(const ComponentId& id, const ComponentPtr& comp);
    ComponentPtr GetComponent(const ComponentId& id);
    const Vector2& GetPosition() const;
    void SetPosition(const Vector2& position);

    void Update(uint64_t frame);
    
private:
    Vector2 position_;
    std::array<ComponentPtr, ComponentIdLast> components_;
};

#endif
