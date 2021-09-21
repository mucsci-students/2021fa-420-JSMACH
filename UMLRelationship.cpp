#include "UMLRelationship.h"
#include "UMLClass.h"
#include <string>

UMLRelationship::UMLRelationship(){};

UMLRelationship::UMLRelationship(UMLClass& src, UMLClass& dest)
  : ClassSrc(&src), ClassDest (&dest)
{
}

UMLRelationship::~UMLRelationship(){};

const UMLClass& UMLRelationship::get_src_class() const 
{
  return *(this->ClassSrc);
}
const UMLClass& UMLRelationship::get_dest_class() const 
{
  return *(this->ClassDest);
}

void to_json(json& j, const UMLRelationship& ur)
{
	j = json {{"ClassSrc", ur.get_src_class().get_class_name()}, {"ClassDest", ur.get_dest_class().get_class_name()}};
}

//THERE IS NO FROM JSON. PAIN.
