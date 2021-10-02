#include "MethodParameter.h"
#include <string>

MethodParameter::MethodParameter(std::string paramName)
	: ParameterName(paramName)
{}

MethodParameter::~MethodParameter()
{}

std::string MethodParameter::get_name()
{
	return this->ParameterName;
}

void MethodParameter::set_name(std::string newName)
{
	this->ParameterName = newName;
}