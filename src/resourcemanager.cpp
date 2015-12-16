#include "resourcemanager.h"

#include "global.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/log/trivial.hpp>
#include <iterator>
#include "log.h"

static ResourceManager* instance = nullptr;

void ResourceManager::CreateInstance()
{
    if(!instance)
    {
        Trace("ResourceManager::CreateInstance()");
        instance = new ResourceManager();
    }
}

void ResourceManager::DestroyInstance()
{
    Trace("ResourceManager::DestroyInstance() %p", (void*)instance);
    delete instance;
    instance = nullptr;
}

ResourceManager& ResourceManager::GetInstance()
{
    return *instance;
}

ResourceManager::ResourceManager()
{
    resourcePath_ = "data";

    char *resourcePathEnv = getenv("RESOURCE_PATH");
    if(resourcePathEnv)
    {
        resourcePath_ = resourcePathEnv;
    }

    UpdateResources();
}

ResourceManager::~ResourceManager()
{
    ;
}

bool ResourceManager::LoadResource(ResourceId id)
{
    auto fileMapItr = resourceFiles_.find(id);
    if(fileMapItr == resourceFiles_.end())
    {
        Warn("ResourceManager::LoadResource invalid resource id: ",  boost::lexical_cast<std::string>(id).c_str());
        return false;
    }
    else
    {
        auto resourceItr = resources_.find(id);
        if(resourceItr!=resources_.end())
        {
            return true;
        }
        else
        {
            //Load the resource file
            return LoadResourceFile(id, fileMapItr->second);
        }
    }

    return true;
}

std::shared_ptr<Resource> ResourceManager::GetResource(ResourceId id)
{
    std::shared_ptr<Resource> res;
    auto itr = resources_.find(id);
    if(itr == resources_.end())
    {
        Warn("ResourceManager::GetResource invalid resource id: %s", boost::lexical_cast<std::string>(id).c_str());
    }
    else
    {
        res = itr->second;
    }
    return res;
}

void ResourceManager::AddResourceLoader(const ResourceLoader& loader)
{
    loaders_.insert(std::make_pair(loader.type, loader));
}

std::string ResourceManager::GetResourcePath(const std::string& file) const
{
    return resourcePath_ + std::string("/") + file;
}

void ResourceManager::UpdateResources()
{
    resourceFiles_.clear();

    Trace("ResourceManager::UpdateResources %s", resourcePath_.c_str());
    boost::filesystem::path path(resourcePath_);
    if(boost::filesystem::exists(path))
    {
        // iterate the resource path looking for resource files
        std::vector<boost::filesystem::path> files;
        std::copy(boost::filesystem::directory_iterator(path), boost::filesystem::directory_iterator(), std::back_inserter(files));

        for(auto p : files)
        {
            Trace("ResourceManager::UpdateResources : %s", p.string().c_str());
            if(boost::filesystem::is_regular_file(p) && p.extension() == std::string(".xml"))
            {
                CacheResourceId(p.string());
            }
        }
    }
}

bool ResourceManager::LoadResourceFile(ResourceId id, const std::string& filename)
{
    Trace("Loading file '%s' for resource %s", filename.c_str(), boost::lexical_cast<std::string>(id).c_str());
    ///\TODO: Add some better error checking / reporting in here
    rapidxml::file<> resfile(filename.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(resfile.data());

    rapidxml::xml_node<> *node = doc.first_node("resource");
    do
    {
        if(node)
        {
            // ensure that the uuid matches up
            rapidxml::xml_attribute<> *resourceIdNode = node->first_attribute("uuid");
            ResourceId resourceId = Resource::StringToResourceId(resourceIdNode->value());
            if(resourceId == id)
            {
                for(rapidxml::xml_node<> *dependency = node->first_node("reference"); dependency!=nullptr; dependency = dependency->next_sibling("reference"))
                {
                    rapidxml::xml_attribute<> *referenceIdNode = dependency->first_attribute("uuid");
                    ResourceId referenceId = Resource::StringToResourceId(referenceIdNode->value());
                    if(!IsResourceLoaded(referenceId))
                    {
                        Trace("Loading resource %s as dependency", boost::lexical_cast<std::string>(referenceId).c_str());
                        if(!LoadResource(referenceId))
                        {
                            Error("Unable to load %s  as dependency for %s", boost::lexical_cast<std::string>(referenceId).c_str(), boost::lexical_cast<std::string>(id).c_str());
                            return false;
                        }
                    }
                }

                rapidxml::xml_attribute<> *attr = node->first_attribute("type");
                if(attr)
                {
                    ResourceType type = Resource::StringToResourceType(attr->value());
                    auto itr = loaders_.find(type);
                    if(itr != loaders_.end())
                    {
                        std::shared_ptr<Resource> resource = itr->second.load_fun(doc);
                        if(!!resource)
                        {
                            resources_[id] = resource;
                            break;
                        }
                    }
                }
                else
                {
                    Error("'%s' did not contain valid type field for resource", filename.c_str());
                    return false;
                }
            }
        }
        else
        {
            Error("'%s' did not contain valid resource node", filename.c_str());
            return false;
        }
        
        node = node->next_sibling("resource");
    } while(node);

    return true;
}

bool ResourceManager::IsResourceLoaded(ResourceId id) const
{
    auto itr = resources_.find(id);
    if(itr == resources_.end())
    {
        return false;
    }
    return true;
}

std::string ResourceManager::FileToString(const std::string& filename) const
{
    std::string file;
    std::ifstream in(filename);
    while(in.is_open() && !in.eof())
    {
        std::string line;
        std::getline(in, line);
        file += line + "\n";
    }
    in.close();
    return file;
}

void ResourceManager::CacheResourceId(const std::string& filepath)
{
    rapidxml::file<> resfile(filepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(resfile.data());
    rapidxml::xml_node<> *node = doc.first_node("resource");
    while(node)
    {
        rapidxml::xml_attribute<> *attr = node->first_attribute("uuid");
        if(!attr)
        {
            return;
        }
        
        std::string uuidStr(attr->value(), attr->value_size());
        ResourceId uuid = Resource::StringToResourceId(uuidStr.c_str());

        resourceFiles_.insert(std::make_pair(uuid, filepath));

        Trace("ResourceManager::CacheResourceId: %s : '%s'", uuidStr.c_str(), filepath.c_str());
        
        node = node->next_sibling("resource");
    }
}

#if 0
extern "C"
{
    ResourceLoader nullLoader;
    ResourceLoader imageAtlasLoader;
    ResourceLoader imageLoader;

    void test_resourcemgr()
    {
        ResourceManager::CreateInstance();
        ResourceId id;
        try {
            id = Resource::StringToResourceId("8eb401f0-78ed-11e5-8bcf-feff819cdc9f");

/*
            nullLoader.type = Resource::StringToResourceType("ce2f105b-2538-43ea-9eb0-24b1fc1c97cb");
            nullLoader.load_fun = [](rapidxml::xml_document<> &doc) -> std::shared_ptr<Resource>
            {
                BOOST_LOG_TRIVIAL(trace)<<"Null Resource Loader";
                return std::shared_ptr<Resource>();
            };
*/
            imageAtlasLoader.type = Resource::StringToResourceType("ce2f105b-2538-43ea-9eb0-24b1fc1c97cb");
            imageAtlasLoader.load_fun = [](rapidxml::xml_document<> &doc) -> std::shared_ptr<Resource>
            {
                BOOST_LOG_TRIVIAL(trace)<<"Image Atlas Resource Loader";
                return ImageAtlas::Load(doc);
            };

            imageLoader.type = Resource::StringToResourceType("89d94ad2-a732-49de-8ef5-ca9579c000d3");
            imageLoader.load_fun = [](rapidxml::xml_document<> &doc) -> std::shared_ptr<Resource>
            {
                BOOST_LOG_TRIVIAL(trace)<<"Image Resource Loader";
                return Image::Load(doc);
            };
        }
        catch(...)
        {
        }
        ResourceManager::GetInstance().AddResourceLoader(imageAtlasLoader);
        ResourceManager::GetInstance().AddResourceLoader(imageLoader);
        ResourceManager::GetInstance().LoadResource(id);
        ResourceManager::DestroyInstance();
    }
}
#endif

namespace rapidxml
{
    void parse_error_handler(char const* str, void* ptr)
    {
        Error(str);
    }
}
