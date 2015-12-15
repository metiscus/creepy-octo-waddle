#ifndef OBJECTGROUP_H_INCLUDED
#define OBJECTGROUP_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "rapidxml/rapidxml.hpp"
#pragma GCC diagnostic pop
#include <memory>

class MapObject;

class ObjectGroup
{
public:
    ObjectGroup();
    ObjectGroup( rapidxml::xml_node<>* node );
    void Load( rapidxml::xml_node<>* groupNode );
    //void save( rapidxml::xml_node<>* mapNode );

    typedef std::vector< std::shared_ptr<MapObject> > ObjectList;

    ObjectList getObjects();
    size_t getObjectCount() const;

private:
    std::string name_;
    ObjectList mObjects;
};



#endif /* OBJECTGROUP_H_INCLUDED */
