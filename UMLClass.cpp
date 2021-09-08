#include "UMLClass.h"
#include "UMLAttribute.h"

UMLClass::~UMLClass(){}	

UMLClass::UMLClass(std::string name){
	this->ClassName = name;
}

UMLClass::UMLClass(std::string name, std::vector<UMLAttribute> attributes) {
	this->ClassName = name;
	this->ClassAttributes = attributes;
}

std::string UMLClass::get_class_name() {
	return this->ClassName;
}

void UMLClass::set_class_name(std::string newName){
	this->ClassName = newName;
}

std::vector<UMLAttribute> UMLClass::get_all_attributes() {
	return this->ClassAttributes;
}

bool UMLClass::operator==(const UMLClass& u) const
{
	return ClassName == u.ClassName;
}