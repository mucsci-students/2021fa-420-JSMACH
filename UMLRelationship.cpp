#include "UMLRelationship.h"
#include "UMLClass.h"
#include <string>

UMLRelationship::UMLRelationship(){};

UMLRelationship::UMLRelationship(UMLClass src, UMLClass dest)
  : ClassSrc(src), ClassDest (dest)
{
}

UMLRelationship::~UMLRelationship(){};

UMLClass UMLRelationship::get_src_class() const {
  return this->ClassSrc;
}
UMLClass UMLRelationship::get_dest_class() const {
  return this->ClassDest;
}
