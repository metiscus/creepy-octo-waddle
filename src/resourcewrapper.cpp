#include "resourcewrapper.h"
#include "log.h"

ResourceWrapper::ResourceWrapper(const std::string& name)
: name_(name)
{
    ;
}

void ResourceWrapper::AddBool(const std::string& name, bool* ref)
{
    types_[name] = BoolType;
    bools_.insert(std::make_pair(name, ref));
}

void ResourceWrapper::AddFloat(const std::string& name, float* ref)
{
    types_[name] = FloatType;
    floats_.insert(std::make_pair(name, ref));
}

void ResourceWrapper::AddVector(const std::string& name, Vector* ref)
{
    types_[name] = VectorType;
    vectors_.insert(std::make_pair(name, ref));
}

void ResourceWrapper::AddUint(const std::string& name, uint32_t* ref)
{
    types_[name] = UintType;
    uints_.insert(std::make_pair(name, ref));
}

void ResourceWrapper::AddInt(const std::string& name, int32_t* ref)
{
    types_[name] = IntType;
    ints_.insert(std::make_pair(name, ref));
}

void ResourceWrapper::AddString(const std::string& name, std::string* ref)
{
    types_[name] = StringType;
    strings_.insert(std::make_pair(name, ref));
}

bool ResourceWrapper::ParseXML(rapidxml::xml_node<> *node)
{
    Assert(node);
    while(node && node->name())
    {
        std::string node_name (node->name());
        auto type = types_.find(node_name);
        if(type == types_.end())
        {
            Warn("Unwrapped field seen in XML '%s'", node_name.c_str());
        }
        else
        {
            if(!node->value())
            {
                Warn("Node '%s' has an empty value", node_name.c_str());
                
            }
            else
            {
                std::string value = node->value();
                switch(type->second)
                {
                    case BoolType:
                    {
                        auto data = bools_.find(node_name);
                        if(value == "true")
                            *data->second = true;
                        else if(value == "false")
                            *data->second = false;
                        break;
                    }
                    
                    case FloatType:
                    {
                        auto data = floats_.find(node_name);
                        *data->second = (float)atof(value.c_str());
                        break;
                    }
                    
                    case VectorType:
                    {
                        auto data = floats_.find(node_name);
                        *data->second = (float)atof(value.c_str());
                        break;
                    }
                }
            }
        }
    }
}