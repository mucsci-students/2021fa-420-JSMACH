#include "UMLRelationship.h"
#include "UMLClass.h"
#include <string>

UMLRelationship::UMLRelationship(std::string name, UMLClass src, UMLClass dest)
  : RelationshipName(name), ClassSrc(src), ClassDest (dest)
{
}

UMLRelationship::~UMLRelationship(){};

std::string UMLRelationship::get_relationship_name() const {
  return this->RelationshipName;
}
UMLClass UMLRelationship::get_src_class() const {
  return this->ClassSrc;
}
UMLClass UMLRelationship::get_dest_class() const {
  return this->ClassDest;
}

void to_json(json& j, const UMLRelationship& ur)
{
  j = json{{"name", ur.get_relationship_name()}, {"src_class", ur.get_src_class()}, {"dest_class", ur.get_dest_class()}};
}

void from_json(json& j, const UMLRelationship& ur)
{
  
};
  
