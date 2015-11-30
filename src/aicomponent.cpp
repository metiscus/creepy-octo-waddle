#include "aicomponent.h"

AIComponent::AIComponent()
    : world_(nullptr)
{

}

void AIComponent::SetWorld(AIWorld* world)
{
    world_ = world;
}

void AIComponent::Update(uint64_t frame)
{
    // do nothing
    (void)frame;
}
