#include "ClassField.h"
#include <string>
#include "UMLClass.h"

ClassField::ClassField() {}

ClassField::ClassField(std::string name)
  : FieldName(name)
{}

ClassField::~ClassField()
{}

std::string ClassField::get_field_name() const
{
  return this->FieldName;
}

void ClassField::set_field_name(std::string newName)
{
  this->FieldName = newName;
}

void to_json(json& j, const ClassField& cf)
{
	j = json{ {"name", cf.get_field_name()} };
}

void from_json(const json& j, ClassField& cf)
{
	cf.set_field_name(j.at("name"));
}
