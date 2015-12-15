#ifndef MAPOBJECT_H_INCLUDED
#define MAPOBJECT_H_INCLUDED

#include <cstdint>
#include <string>
#include <map>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "rapidxml/rapidxml.hpp"
#pragma GCC diagnostic pop

typedef std::map<std::string, std::string> PropertyMap;

class MapObject
{
public:
    enum ObjectType {
        InvalidType,
        RectangleType,
        PolygonType,
        PolyLineType,
    };

    MapObject(ObjectType type, uint32_t x, uint32_t y);
    virtual ~MapObject();

    uint32_t getX() const;
    uint32_t getY() const;

    bool hasProperty(const std::string& name) const;
    std::string getProperty(const std::string& name) const;

    static MapObject* Load(rapidxml::xml_node<>* objectNode);
    virtual void save(rapidxml::xml_node<>* node) = 0;

    ObjectType getObjectType() const;

protected:
    MapObject();
    void setPosition(uint32_t x, uint32_t y);

private:
    uint32_t mX;
    uint32_t mY;
    PropertyMap mProperties;
    ObjectType mObjectType;
};

class Rectangle : public MapObject
{
public:
    Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    virtual ~Rectangle();

    uint32_t getW() const;
    uint32_t getH() const;

    virtual void save( rapidxml::xml_node<>* node );

private:
    uint32_t width_;
    uint32_t height_;

    friend class MapObject;

    Rectangle();
    void setSize(uint32_t width, uint32_t height);
};

class Polygon : public MapObject
{
public:
    Polygon(uint32_t x, uint32_t y, std::vector<glm::ivec2> points);
    virtual ~Polygon();

    std::vector<glm::ivec2> getPoints() const;

    virtual void save( rapidxml::xml_node<>* node );

private:
    std::vector<glm::ivec2> mPoints;

    friend class MapObject;
    Polygon();
    void setPoints(std::vector<glm::ivec3> points);
};

class PolyLine : public MapObject
{
public:
    PolyLine(uint32_t x, uint32_t y, std::vector<glm::ivec2> points);
    virtual ~PolyLine();

    std::vector<glm::ivec2> getPoints() const;

    virtual void save( rapidxml::xml_node<>* node );

private:
    std::vector<glm::ivec2> mPoints;

    friend class MapObject;
};


#endif /* MAPOBJECT_H_INCLUDED */
