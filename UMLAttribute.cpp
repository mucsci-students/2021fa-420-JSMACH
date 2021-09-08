#include "UMLAttribute.h"
#include <string>
#include "UMLClass.h"

UMLAttribute::UMLAttribute(std::string name) {
  this->AttributeName= name;
}

std::string UMLAttribute::get_attribute_name(){
  return this->AttributeName;
}

void set_attribute_name(std::string newName){
   this->AttributeName= name;
}
