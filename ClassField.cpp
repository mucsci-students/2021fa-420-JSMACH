#include "ClassField.h"
#include <string>
#include "UMLClass.h"


ClassField::ClassField(std::string name)
  : FieldName(name)
{}

std::string ClassField::get_field_name() const{
  return this->FieldName;
}

void ClassField::set_field_name(std::string newName){
  this->FieldName = newName;
}