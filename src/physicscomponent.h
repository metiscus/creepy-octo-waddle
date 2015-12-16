#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include "component.h"
#include "vector.h"

class PhysicsComponent : public Component
{
    bool is_static_;
    Vector velocity_;

public:
    PhysicsComponent();
    PhysicsComponent(const ResourceId& id);
    virtual ~PhysicsComponent() = default;

    static const ResourceType TypeId;
    static std::shared_ptr<Resource> Load(rapidxml::xml_document<> &doc);

    static ComponentId GetComponentId();

    void SetIsStatic(bool is_static);
    void SetVelocity(const Vector& velocity);
    void AddVelocity(const Vector& velocity);
    const Vector& GetVelocity() const;
    bool GetIsStatic() const;

    virtual void Update(uint64_t frame);
};

#endif // PHYSICS_COMPONENT_H_INCLUDED
