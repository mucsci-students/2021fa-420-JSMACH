#include "UMLRelationship.h"
#include <string>

UMLRelationship::UMLRelationship(std::string name, UMLClass src, UMLClass dest)
  : RelationshipName(name), ClassSrc(src), ClassDest (dest)
{
}

auto UMLRelationship::get_relationship_name(){
  return this->RelationshipName;
}
auto UMLRelationship::get_src_class(){
  return this->ClassSrc;
}
auto UMLRelationship:: get_dest_class(){
  return this->ClassDest;
}
  
