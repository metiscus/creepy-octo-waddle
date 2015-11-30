#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <cstdint>
#include <memory>

class Object;

class Component
{
    Object* parent_;
public:
    Component();
    virtual ~Component();

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    void SetParent(Object* parent);
    const Object* GetParent() const;
    Object* GetParent();
};

#endif
