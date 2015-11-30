#include "object.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::SetComponent(const ComponentId& id, std::shared_ptr<Component> comp)
{
    components_[id] = comp;
}

std::shared_ptr<Component> Object::GetComponent(const ComponentId& id)
{
    return components_[id];
}

const Vector2& Object::GetPosition() const
{
    return position_;
}

void Object::SetPosition(const Vector2& position)
{
    position_ = position;
}
