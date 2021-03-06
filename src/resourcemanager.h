#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include "global.h"
#include <boost/uuid/uuid.hpp>
#include "resource.h"

struct ResourceLoader
{
    ResourceType type;
    std::shared_ptr<Resource> (*load_fun)(rapidxml::xml_document<> &doc);
};

class ResourceManager
{
public:
    static void CreateInstance();
    static void DestroyInstance();
    static ResourceManager& GetInstance();

    bool LoadResource(ResourceId resource);
    std::shared_ptr<Resource> GetResource(ResourceId resource);

    void AddResourceLoader(const ResourceLoader& loader);
    
    std::string GetResourcePath(const std::string& file) const;

private:
    std::string resourcePath_;

    std::map<ResourceId, std::string> resourceFiles_;
    std::map<ResourceId, std::shared_ptr<Resource> > resources_;
    std::map<ResourceType, ResourceLoader> loaders_;

    ResourceManager();
    ~ResourceManager();

    void UpdateResources();
    void CacheResourceId(const std::string& filepath);
    std::string FileToString(const std::string& filename) const;
    bool LoadResourceFile(ResourceId id, const std::string& filename);
    bool IsResourceLoaded(ResourceId id) const;
};

#endif // RESOURCEMANAGER_H_INCLUDED
