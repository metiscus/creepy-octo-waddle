#include "object.h"
#include "component.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::SetComponent(const ComponentId& id, const ComponentPtr& comp)
{
    components_[id] = comp;
    comp->SetParent(this);
}

const Vector& Object::GetPosition() const
{
    return position_;
}

void Object::SetPosition(const Vector& position)
{
    position_ = position;
}

void Object::Update(uint64_t frame)
{
    for(auto comp : components_)
    {
    	if(comp)
    	{
    	    comp->Update(frame);
    	}
    }
}
