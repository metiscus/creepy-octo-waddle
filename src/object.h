#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <array>
#include <memory>
#include "vector.h"

class Component;

enum ComponentId
{
    ComponentLast
};

class Object
{
public:
    Object();
    ~Object();

    void SetComponent(const ComponentId& id, std::shared_ptr<Component> comp);
    std::shared_ptr<Component> GetComponent(const ComponentId& id);
    const Vector2& GetPosition() const;
    void SetPosition(const Vector2& position);
    
private:
    Vector2 position_;
    std::array<std::shared_ptr<Component>, ComponentLast> components_;
};

#endif
