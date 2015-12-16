#include "aicomponent.h"
#include "physicscomponent.h"
#include "object.h"

const ResourceType AIComponent::TypeId = 
{
    0x89, 0xd9, 0x4a, 0xd2,
    0xa7, 0x32,
    0x49, 0xde,
    0x8e, 0xf5,
    0xca, 0x95, 0x79, 0xc0, 0x00, 0xd6
};

AIComponent::AIComponent()
    : Component(TypeId)
    , world_(nullptr)
{

}

ComponentId AIComponent::GetComponentId()
{
    return AIComponentId;
}

void AIComponent::SetWorld(AIWorld* world)
{
    world_ = world;
}

void AIComponent::Update(uint64_t frame)
{
    (void)frame;

    // if not at the goal position, move towards it
    if(fabs(max_speed_-0.0001) > 0)
    {
        const Vector& position = GetParent()->GetPosition();
        Vector toGoal = (goal_position_ - position);
        float distanceToGoal = toGoal.Length();
        float speed = max_speed_;
        if(distanceToGoal < max_speed_)
        {
            speed = distanceToGoal;
        }
        toGoal /= distanceToGoal;
        GetParent()->GetComponent<PhysicsComponent>()->SetVelocity(toGoal * speed);
    }
}

void AIComponent::SetGoalPosition(const Vector& position)
{
    goal_position_ = position;
}

void AIComponent::SetMaxSpeed(float speed)
{
    max_speed_ = speed;
}

const Vector& AIComponent::GetGoalPosition() const
{
    return goal_position_;
}

float AIComponent::GetMaxSpeed() const
{
    return max_speed_;
}
