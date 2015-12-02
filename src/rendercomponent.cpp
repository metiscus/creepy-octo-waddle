#include <cassert>
#include "rendercomponent.h"
#include "object.h"


RenderComponent::RenderComponent()
{
    ;
}

ComponentId RenderComponent::GetComponentId()
{
    return RenderComponentId;
}

void RenderComponent::AddDrawable(const DrawablePtr& drawable)
{
    drawables_.emplace_back(drawable);
}

const std::vector<DrawablePtr>& RenderComponent::GetDrawables() const
{
    return drawables_;
}

std::vector<DrawablePtr> RenderComponent::GetDrawables()
{
    return drawables_;
}

void RenderComponent::Update(uint64_t frame)
{
    assert(GetParent());
    const Vector2& position = GetParent()->GetPosition();
    for(auto drawable : drawables_)
    {
        drawable->SetPosition(position);
        drawable->Update(frame);
    }
}

RenderComponent* RenderComponent::AsRenderComponent()
{
    return this;
}
