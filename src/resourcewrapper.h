#ifndef RESOURCEWRAPPER_H_INCLUDED
#define RESOURCEWRAPPER_H_INCLUDED

#include "global.h"
#include "vector.h" 

class ResourceWrapper
{
public:
    ResourceWrapper(const std::string& name);
    void AddBool(const std::string& name, bool* ref);
    void AddFloat(const std::string& name, float* ref);
    void AddVector(const std::string& name, Vector* ref);
    void AddUint(const std::string& name, uint32_t* ref);
    void AddInt(const std::string& name, int32_t* ref);
    void AddString(const std::string& name, std::string* ref);

    bool ParseXML(rapidxml::xml_node<> *node);

private:
    std::string name_;
    enum FieldType{
        BoolType,
        FloatType,
        VectorType,
        UintType,
        IntType,
        StringType
    };
    std::map<std::string, FieldType> types_;
    std::map<std::string, bool*> bools_;
    std::map<std::string, float*> floats_;
    std::map<std::string, Vector*> vectors_;
    std::map<std::string, uint32_t*> uints_;
    std::map<std::string, int32_t*> ints_;
    std::map<std::string, std::string*> strings_;
};

#endif // RESOURCEWRAPPER_H_INCLUDED