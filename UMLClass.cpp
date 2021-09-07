#include "UMLClass.h"
#include "UMLAttribute.h"

UMLClass::UMLClass(std::string name) {
	this->ClassName = name;
}

std::string UMLClass::get_class_name() {
	return this->ClassName;
}

std::vector<UMLAttribute> UMLClass::get_all_attributes() {
	return this->ClassAttributes;
}