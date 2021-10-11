#include "UMLClass.h"
#include "ClassField.h"
#include "ClassMethod.h"

UMLClass::~UMLClass(){}	

UMLClass::UMLClass(){}

UMLClass::UMLClass(std::string name)
	: ClassName (name)
{}

UMLClass::UMLClass(std::string name, std::vector<ClassField> fields, std::vector<ClassMethod> methods)
	: ClassName(name), Fields(fields), Methods(methods)
{}

std::vector<ClassField>::iterator UMLClass::get_iterator_to_field_name(std::string fieldName)
{
	for (auto iter = Fields.begin(); iter != Fields.end(); iter++)
	{
		if ((*iter).get_field_name() == fieldName)
		{
			return iter;
		}
	}

	return Fields.end();
}

std::vector<ClassMethod>::iterator UMLClass::get_iterator_to_method_name(std::string methodName)
{
	for (auto iter = Methods.begin(); iter != Methods.end(); iter++)
	{
		if ((*iter).get_method_name() == methodName)
		{
			return iter;
		}
	}

	return Methods.end();
}

bool UMLClass::does_field_already_exist(std::string fieldName)
{
	return get_iterator_to_field_name(fieldName) != Fields.end();
}

bool UMLClass::does_method_already_exist(std::string methodName)
{
	return get_iterator_to_method_name(methodName) != Methods.end();
}

std::string UMLClass::get_class_name() const 
{
	return this->ClassName;
}

void UMLClass::set_class_name(std::string newName)
{
	this->ClassName = newName;
}


std::vector<ClassField> UMLClass::get_all_fields() const
{
	return Fields;
}

bool UMLClass::add_field(ClassField field)
{
	if (does_field_already_exist(field.get_field_name()))
	{
		return false;
	}
	else
	{
		Fields.push_back(field);
		return true;
	}
}

bool UMLClass::remove_field(std::string fieldName)
{
	if (!does_field_already_exist(fieldName))
	{
		return false;
	}
	else
	{
		auto iter = get_iterator_to_field_name(fieldName);
		Fields.erase(iter);
		return true;
	}
}

bool UMLClass::rename_field(std::string fieldNameFrom, std::string fieldNameTo)
{
	if (does_field_already_exist(fieldNameTo) || !does_field_already_exist(fieldNameFrom))
	{
		return false;
	}
	else
	{
		auto iter = get_iterator_to_field_name(fieldNameFrom);
		(*iter).set_field_name(fieldNameTo);
		return true;
	}
}

std::vector<ClassMethod> UMLClass::get_all_methods() const
{
	return Methods;
}

bool UMLClass::add_method(ClassMethod method)
{
	if (does_method_already_exist(method.get_method_name()))
	{
		return false;
	}
	else
	{
		Methods.push_back(method);
		return true;
	}
}

bool UMLClass::remove_method(std::string methodName)
{
	if (!does_method_already_exist(methodName))
	{
		return false;
	}
	else
	{
		auto iter = get_iterator_to_method_name(methodName);
		Methods.erase(iter);
		return true;
	}
}

bool UMLClass::rename_method(std::string methodNameFrom, std::string methodNameTo)
{
	if (does_method_already_exist(methodNameTo) || !does_method_already_exist(methodNameFrom))
	{
		return false;
	}
	else
	{
		auto iter = get_iterator_to_method_name(methodNameFrom);
		(*iter).set_method_name(methodNameTo);
		return true;
	}
}

bool UMLClass::add_method_parameter(std::string methodName, MethodParameter methodParam)
{
	auto iter = get_iterator_to_method_name(methodName);
	if (iter == Methods.end())
	{
		return false;
	}
	else
	{
		return (*iter).add_parameter(methodParam);
	}
}

bool UMLClass::remove_method_parameter(std::string methodName, std::string methodParamName)
{
	auto iter = get_iterator_to_method_name(methodName);
	if (iter == Methods.end())
	{
		return false;
	}
	else
	{
		return (*iter).remove_parameter(methodParamName);
	}
}

bool UMLClass::rename_method_parameter(std::string methodName, std::string methodParamNameFrom, std::string methodParamNameTo)
{
	auto iter = get_iterator_to_method_name(methodName);
	if (iter == Methods.end())
	{
		return false;
	}
	else
	{
		return (*iter).rename_parameter(methodParamNameFrom, methodParamNameTo);
	}
}

bool UMLClass::does_method_parameter_exist(std::string methodName, std::string methodParamName)
{
	auto iter = get_iterator_to_method_name(methodName);
	if (iter == Methods.end())
	{
		return false;
	}
	else
	{
		return (*iter).does_parameter_exist(methodParamName);
	}
}

bool UMLClass::operator==(const UMLClass& u) const
{
	return ClassName == u.ClassName;
}

void to_json(json& j, const UMLClass& uc)
{
	j = json{
		{"name", uc.get_class_name()},
		{"fields", uc.get_all_fields()},
		{"methods", uc.get_all_methods()}
	};
}

void from_json(const json& j, UMLClass& uc)
{
	uc.set_class_name(j.at("name"));
	std::list<ClassField> fields = j.at("fields");
	for (ClassField cf : fields)
		uc.add_field(cf);
	std::list<ClassMethod> methods = j.at("methods");
	for (ClassMethod cm : methods)
		uc.add_method(cm);
}