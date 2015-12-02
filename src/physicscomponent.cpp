#include "physicscomponent.h"
#include "object.h"
#include <cassert>

PhysicsComponent::PhysicsComponent()
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

void PhysicsComponent::SetVelocity(const Vector2& velocity)
{
    velocity_ = velocity;
}

void PhysicsComponent::AddVelocity(const Vector2& velocity)
{
    velocity_ += velocity;
}

const Vector2& PhysicsComponent::GetVelocity() const
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
        Vector2 position = GetParent()->GetPosition();
        position += velocity_;
        GetParent()->SetPosition(position);
    }
}
