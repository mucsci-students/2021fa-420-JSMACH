#include "UMLRelationship.h"
#include "UMLClass.h"
#include "UMLException.hpp"
#include <string>
#include <cstring>

//#define strcasecmp _stricmp

UMLRelationship::UMLRelationship(){};

UMLRelationship::UMLRelationship(UMLClass& src, UMLClass& dest)
  : ClassSrc(&src), ClassDest (&dest)
{
}

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

std::string UMLRelationship::type_to_string() const
{
  if(Type == RelationshipType::Aggregation)
  {
    return "aggregation";
  }
  else if(Type == RelationshipType::Composition)
  {
    return "composition";
  }
  else if(Type == RelationshipType::Inheritance)
  {
    return "inheritance";
  }
  else if(Type == RelationshipType::Realization)
  {
    return "realization";
  }
  return "";
}

RelationshipType UMLRelationship::type_from_string(std::string typeName)
{
  if(strcasecmp(typeName.c_str(), "Aggregation") == 0)
  {
    return RelationshipType::Aggregation;
  }
  else if(strcasecmp(typeName.c_str(), "Composition") == 0)
  {
    return RelationshipType::Composition;
  }
  else if(strcasecmp(typeName.c_str(), "Inheritance") == 0)
  {
    return RelationshipType::Inheritance;
  }
  else if(strcasecmp(typeName.c_str(), "Realization")  == 0)
  {
    return RelationshipType::Realization;
  }

  throw UMLErrorCode::no_such_relationship_type;
}

void UMLRelationship::set_type(std::string typeName)
{
  RelationshipType newType = type_from_string(typeName);
  this->Type = newType;
}

void to_json(json& j, const UMLRelationship& ur)
{
	j = json {
        {"source", ur.get_src_class().get_class_name()}, 
        {"destination", ur.get_dest_class().get_class_name()},
        {"type", ur.type_to_string()}
    };
}



//THERE IS NO FROM JSON. PAIN.
