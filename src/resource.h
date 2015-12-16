#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include "global.h"
#include "log.h"

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid.hpp>

typedef boost::uuids::uuid ResourceId;
typedef boost::uuids::uuid ResourceType;

class Resource
{
public:
    Resource(const ResourceType& type)
       : uuid_(boost::uuids::random_generator()())
       , type_(type)
    {
        ;
    }
    
    Resource(const ResourceId& uuid, const ResourceType& type)
        : uuid_(uuid)
        , type_(type)
        {}

    Resource(const Resource&) = delete;

    virtual ~Resource() = default;
    
    Resource& operator=(const Resource&) = delete;

    inline const ResourceId GetResourceId() const
    {
        return uuid_;
    }

    inline const ResourceType GetResourceType() const
    {
        return type_;
    }

    static ResourceId StringToResourceId(const char* ptr)
    {
        Assert(ptr);
        boost::uuids::string_generator generator;
        return generator(ptr);
    }

    static ResourceType StringToResourceType(const char* ptr)
    {
        Assert(ptr);
        boost::uuids::string_generator generator;
        return generator(ptr);
    }

private:
    const ResourceId uuid_;
    const ResourceType type_;
};

#endif // RESOURCE_H_INCLUDED
