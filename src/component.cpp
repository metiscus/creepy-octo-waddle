#include "component.h"

Component::Component()
    : parent_(nullptr)
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

AIComponent* Component::AsAIComponent()
{
    return nullptr;
}
