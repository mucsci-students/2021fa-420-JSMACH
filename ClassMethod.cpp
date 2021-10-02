#include "ClassMethod.h"
#include <string>
#include <list>
#include "UMLClass.h"
#include "MethodParameter.h"

ClassMethod::ClassMethod(std::string name)
  : ClassMethodName(name)
{}

ClassMethod::ClassMethod(std::string name, std::list<MethodParameter> parameters)
  : ClassMethodName(name), MethodParameters(parameters)
{}

ClassMethod::~ClassMethod()
{}

std::list<MethodParameter>::iterator ClassMethod::get_param_iter_by_name(const std::string& paramName)
{
    if(MethodParameters.empty())
        return MethodParameters.end();

    for(auto iter = MethodParameters.begin(); iter != MethodParameters.end(); iter++)
    {
        if((*iter).get_name() == paramName)
            return iter;
    }

    return MethodParameters.end();
}

bool ClassMethod::does_parameter_exist(const std::string& paramName)
{
    return get_param_iter_by_name(paramName) != MethodParameters.end();
}

std::string ClassMethod::get_method_name() const
{
  return this->ClassMethodName;
}

void ClassMethod::set_method_name(const std::string& newName)
{
  this->ClassMethodName = newName;
}

const std::list <MethodParameter> ClassMethod::get_parameters() const
{
    return this->MethodParameters;
}

bool ClassMethod::add_parameter(MethodParameter parameter)
{
    if(does_parameter_exist(parameter.get_name()))
    {
        return false;
    }
    else
    {
        MethodParameters.push_back(parameter);
        return true;
    }
}

bool ClassMethod::remove_parameter(const std::string& paramName)
{
    auto i = get_param_iter_by_name(paramName);

    if(i == MethodParameters.end())
    {
        return false;
    }
    else
    {
        MethodParameters.erase(i);
        return true;
    }
}

bool ClassMethod::rename_parameter(const std::string& nameFrom, const std::string& nameTo){

    if(does_parameter_exist(nameTo) || !does_parameter_exist(nameFrom))
    {
        return false;
    }
    else
    {
        auto i = get_param_iter_by_name(nameFrom);
        (*i).set_name(nameTo);
        return true;
    }
}
