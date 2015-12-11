#include "aicomponent.h"
#include "physicscomponent.h"
#include "object.h"

AIComponent::AIComponent()
    : world_(nullptr)
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
