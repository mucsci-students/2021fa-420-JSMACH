#include "UMLAttribute.h"
#include <string>
#include "UMLClass.h"

UMLAttribute::UMLAttribute(std::string name)
  : AttributeName(name)
{}

std::string UMLAttribute::get_attribute_name() const{
  return this->AttributeName;
}

void UMLAttribute::set_attribute_name(std::string newName){
  this->AttributeName = newName;
}

void to_json(json& j, const UMLAttribute& ua)
{
  j = json{{"name", ua.get_attribute_name()}};
}

void from_json(json& j, const UMLAttribute& ua)
{

}
