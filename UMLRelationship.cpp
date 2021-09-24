#include "UMLRelationship.h"
#include "UMLClass.h"
#include <string>

UMLRelationship::UMLRelationship(){};

UMLRelationship::UMLRelationship(UMLClass& src, UMLClass& dest, RelationshipType type)
  : ClassSrc(&src), ClassDest (&dest), Type(type)
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

std::string UMLRelationship::type_to_string()
{
  if(type == RelationshipType::Aggregation)
  {
    return "Aggregation";
  }
  else if(type == RelationshipType::Composition)
  {
    return "Composition";
  }
  else if(type == RelationshipType::Inheritance)
  {
    return "Inheritance";
  }
  else if(type == RelationshipType::Realization)
  {
    return "Realization"
  }
}

void to_json(json& j, const UMLRelationship& ur)
{
	j = json {{"ClassSrc", ur.get_src_class().get_class_name()}, {"ClassDest", ur.get_dest_class().get_class_name()}};
}



//THERE IS NO FROM JSON. PAIN.
