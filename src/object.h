#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <array>
#include "component.h"
#include <memory>
#include "vector.h"

class Object
{
public:
    Object();
    ~Object();

    void SetComponent(const ComponentId& id, const ComponentPtr& comp);

    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        return std::static_pointer_cast<T>(components_[T::GetComponentId()]);
    }

    const Vector& GetPosition() const;
    void SetPosition(const Vector& position);

    void Update(uint64_t frame);

private:
    Vector position_;
    std::array<ComponentPtr, ComponentIdLast> components_;
};

#endif
