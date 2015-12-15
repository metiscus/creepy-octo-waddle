#include "objectgroup.h"
#include "mapobject.h"
#include "../log.h"


ObjectGroup::ObjectGroup()
{
}

ObjectGroup::ObjectGroup(rapidxml::xml_node<> *node)
{
    Load(node);
}

void ObjectGroup::Load(rapidxml::xml_node<> *groupNode)
{
    if (!groupNode)
    {
        error("(null) node passed in.");
    }
    else
    {
        for (rapidxml::xml_node<> *itr = groupNode->first_node("object"); itr;
             itr = itr->next_sibling())
        {
            info(itr->value());
            MapObject *pObj = MapObject::Load(itr);
            if (pObj)
            {
                std::shared_ptr<MapObject> ptr;
                ptr.reset(pObj);
                mObjects.push_back(ptr);
            }
        }
    }
}
// void ObjectGroup::save( rapidxml::xml_node<>* mapNode );

ObjectGroup::ObjectList ObjectGroup::getObjects()
{
    return mObjects;
}

size_t ObjectGroup::getObjectCount() const
{
    return mObjects.size();
}
