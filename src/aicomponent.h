#ifndef AICOMPONENT_H_INCLUDED
#define AICOMPONENT_H_INCLUDED

#include "component.h"
#include "vector.h"

class AIWorld;

class AIComponent : public Component
{
    AIWorld* world_;
    Vector goal_position_;
    float max_speed_;

public:
    AIComponent();
    virtual ~AIComponent() = default;

    static ComponentId GetComponentId();

    void SetWorld(AIWorld* world);
    void SetGoalPosition(const Vector& position);
    void SetMaxSpeed(float speed);

    const Vector& GetGoalPosition() const;
    float GetMaxSpeed() const;

    virtual void Update(uint64_t frame);
};

#endif
