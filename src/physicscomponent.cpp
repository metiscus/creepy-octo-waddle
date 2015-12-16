#include "physicscomponent.h"
#include "object.h"
#include <cassert>

const ResourceType PhysicsComponent::TypeId = 
{
    0x89, 0xd9, 0x4a, 0xd2,
    0xa7, 0x32,
    0x49, 0xde,
    0x8e, 0xf5,
    0xca, 0x95, 0x79, 0xc0, 0x00, 0xd4
};

std::shared_ptr<Resource> PhysicsComponent::Load(rapidxml::xml_document<> &doc)
{
    return std::shared_ptr<Resource>();
}

PhysicsComponent::PhysicsComponent()
    : Component(TypeId)
{
    is_static_ = false;
}

PhysicsComponent::PhysicsComponent(const ResourceId& id)
    : Component(id, TypeId)
{
    is_static_ = false;
}

ComponentId PhysicsComponent::GetComponentId()
{
    return PhysicsComponentId;
}

void PhysicsComponent::SetIsStatic(bool is_static)
{
    is_static_ = is_static;
}

void PhysicsComponent::SetVelocity(const Vector& velocity)
{
    velocity_ = velocity;
}

void PhysicsComponent::AddVelocity(const Vector& velocity)
{
    velocity_ += velocity;
}

const Vector& PhysicsComponent::GetVelocity() const
{
    return velocity_;
}

bool PhysicsComponent::GetIsStatic() const
{
    return is_static_;
}

void PhysicsComponent::Update(uint64_t frame)
{
    if(!is_static_)
    {
        assert(GetParent());
        Vector position = GetParent()->GetPosition();
        position += velocity_;
        GetParent()->SetPosition(position);
    }
}
