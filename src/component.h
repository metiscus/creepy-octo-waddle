#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <cstdint>
#include <memory>

class Object;
class AIComponent;
class RenderComponent;

class Component
{
    Object* parent_;
public:
    Component();
    virtual ~Component();

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    virtual void Update(uint64_t frame) = 0;

    void SetParent(Object* parent);
    const Object* GetParent() const;
    Object* GetParent();

    virtual AIComponent* AsAIComponent();
    virtual RenderComponent* AsRenderComponent();
};

typedef std::shared_ptr<Component> ComponentPtr;
#endif
