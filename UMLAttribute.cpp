#include "UMLAttribute.h"
#include <string>
#include "UMLClass.h"

UMLAttribute::UMLAttribute(std::string name)
  : AttributeName(name)
{}

std::string UMLAttribute::get_attribute_name(){
  return this->AttributeName;
}

void UMLAttribute::set_attribute_name(std::string newName){
  this->AttributeName = newName;
}
