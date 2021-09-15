#include "UMLClass.h"
#include "UMLAttribute.h"

UMLClass::~UMLClass(){}	

UMLClass::UMLClass(){}

UMLClass::UMLClass(std::string name)
	: ClassName (name)
{}

UMLClass::UMLClass(std::string name, std::vector<UMLAttribute> attributes)
	: ClassName (name), ClassAttributes (attributes)
{}

std::vector<UMLAttribute>::iterator UMLClass::get_iterator_to_attribute_name(std::string attributeName)
{
	for(auto iter = ClassAttributes.begin(); iter != ClassAttributes.end(); iter++)
	{
		if((*iter).get_attribute_name() == attributeName)
		{
			return iter;
		}
	}
	
	return ClassAttributes.end();
}

bool UMLClass::does_attribute_already_exist(std::string attributeName)
{
	return get_iterator_to_attribute_name(attributeName) != ClassAttributes.end();
}

std::string UMLClass::get_class_name() const {
	return this->ClassName;
}

void UMLClass::set_class_name(std::string newName){
	this->ClassName = newName;
}

std::vector<UMLAttribute> UMLClass::get_all_attributes() const {
	return this->ClassAttributes;
}

bool UMLClass::add_attribute(UMLAttribute attribute)
{
	if(does_attribute_already_exist(attribute.get_attribute_name()))
	{
		return false;
	}
	else
	{
		ClassAttributes.push_back(attribute);
		return true;
	}
}

bool UMLClass::remove_attribute(std::string attributeName)
{
	if(!does_attribute_already_exist(attributeName))
	{
		return false;
	}
	else
	{
		auto iter = get_iterator_to_attribute_name(attributeName);
		ClassAttributes.erase(iter);
		return true;
	}
}

bool UMLClass::operator==(const UMLClass& u) const
{
	return ClassName == u.ClassName;
}

/*
void to_json(json& j, const UMLClass& uc)
{
	j = json {{"name", uc.get_class_name()}, {"attributes", uc.get_all_attributes()}};
}

void from_json(json& j, const UMLClass& uc)
{

}
*/