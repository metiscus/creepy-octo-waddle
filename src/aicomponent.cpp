#include "aicomponent.h"
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
        Vector2 position = GetParent()->GetPosition();
        Vector2 toGoal = (goal_position_ - position).AsUnit();
        position += toGoal * max_speed_;
        GetParent()->SetPosition(position);
    }
}

void AIComponent::SetGoalPosition(const Vector2& position)
{
    goal_position_ = position;
}

void AIComponent::SetMaxSpeed(float speed)
{
    max_speed_ = speed;
}

const Vector2& AIComponent::GetGoalPosition() const
{
    return goal_position_;
}

float AIComponent::GetMaxSpeed() const
{
    return max_speed_;
}
