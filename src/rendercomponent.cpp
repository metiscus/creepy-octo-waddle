#include "rendercomponent.h"
#include "object.h"


RenderComponent::RenderComponent()
{
    ;
}

void RenderComponent::AddDrawable(const Drawable& drawable)
{
    drawables_.emplace_back(drawable);
}

const std::vector<Drawable>& RenderComponent::GetDrawables() const
{
    return drawables_;
}

void RenderComponent::Update(uint64_t frame)
{
    (void)frame;
    const Vector2& position = GetParent()->GetPosition();
    for(auto drawable : drawables_)
    {
        drawable.SetPosition(position);
    }
}

RenderComponent* RenderComponent::AsRenderComponent()
{
    return this;
}
