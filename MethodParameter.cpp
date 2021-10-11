#include "MethodParameter.h"
#include <string>

MethodParameter::MethodParameter() {}

MethodParameter::MethodParameter(std::string paramName)
	: ParameterName(paramName)
{}

MethodParameter::~MethodParameter()
{}

std::string MethodParameter::get_name() const
{
	return this->ParameterName;
}

void MethodParameter::set_name(std::string newName)
{
	this->ParameterName = newName;
}

void to_json(json& j, const MethodParameter& mp)
{
	j = json {{"name", mp.get_name()}};
}

void from_json(const json& j, MethodParameter& mp)
{
	mp.set_name(j.at("name"));
}