#include "component.h"

Component::Component(ResourceType type)
    : Resource(type)
    , parent_(nullptr)
{

}

Component::Component(ResourceId id, ResourceType type)
    : Resource(id, type)
    , parent_(nullptr)
{

}

Component::~Component()
{
    parent_ = nullptr;
}

void Component::SetParent(Object* parent)
{
    parent_ = parent;
}

Object* Component::GetParent()
{
    return parent_;
}

const Object* Component::GetParent() const
{
    return parent_;
}
