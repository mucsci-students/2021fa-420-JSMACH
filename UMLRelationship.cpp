#include "UMLRelationship.h"
#include "UMLClass.h"
#include <string>

UMLRelationship::UMLRelationship(std::string name, UMLClass src, UMLClass dest)
  : RelationshipName(name), ClassSrc(src), ClassDest (dest)
{
}

UMLRelationship::~UMLRelationship(){};

std::string UMLRelationship::get_relationship_name(){
  return this->RelationshipName;
}
UMLClass UMLRelationship::get_src_class(){
  return this->ClassSrc;
}
UMLClass UMLRelationship::get_dest_class(){
  return this->ClassDest;
}
  
