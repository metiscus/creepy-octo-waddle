#ifndef RENDERCOMPONENT_H_INCLUDED
#define RENDERCOMPONENT_H_INCLUDED

#include "component.h"
#include <cstdint>
#include "drawable.h"
#include "render.h"
#include "vector.h"

class RenderComponent : public Component
{
    std::vector<DrawablePtr> drawables_;
public:
    RenderComponent();
    virtual ~RenderComponent() = default;

    static ComponentId GetComponentId();

    void AddDrawable(const DrawablePtr& drawable);
    const std::vector<DrawablePtr>& GetDrawables() const;
    std::vector<DrawablePtr> GetDrawables();

    virtual void Update(uint64_t frame);
    virtual RenderComponent* AsRenderComponent();
};

#endif // RENDERCOMPONENT_H_INCLUDED
