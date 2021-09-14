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
