#include <cassert>
#include "rendercomponent.h"
#include "object.h"

const ResourceType RenderComponent::TypeId = 
{
    0x89, 0xd9, 0x4a, 0xd2,
    0xa7, 0x32,
    0x49, 0xde,
    0x8e, 0xf5,
    0xca, 0x95, 0x79, 0xc0, 0x00, 0xd5
};

std::shared_ptr<Resource> RenderComponent::Load(rapidxml::xml_document<> &doc)
{
    return std::shared_ptr<Resource>();
}

RenderComponent::RenderComponent()
    : Component(TypeId)
{
    ;
}

RenderComponent::RenderComponent(const ResourceId& id)
    : Component(id, TypeId)
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
    const Vector& position = GetParent()->GetPosition();
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
