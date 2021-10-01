#include "ClassMethod.h"
#include <string>
#include <list>
#include "UMLClass.h"

ClassMethod::ClassMethod(std::string name)
  : ClassMethodName(name)
{}

ClassMethod::ClassMethod(std::string name, std::list <std::string> parameters)
  : ClassMethodName(name), ClassParameters(parameters)
{}

std::string ClassMethod::get_param_name(){
 return this->ClassParameters;
}

void ClassMethod::set_param_name(std::string newName){
  this->ClassParameters = newName;
}

std::list<std::string>::iterator ClassMethod::get_param_iter_by_name(const std::string& paramName){
    if(ClassParameters.empty())
    return ClassParameters.end();

    for(auto iter = ClassParameters.begin(); iter != ClassParameters.end(); iter++)
    {
        if((*iter) == paramName)
            return iter;
    }

    return ClassParameters.end();
}

bool ClassMethod::does_parameter_exist(const std::string& paramName){
    return get_param_iter_by_name(paramName) != ClassParameters.end();
}

std::string ClassMethod::get_method_name() const{
  return this->ClassMethodName;
}

void ClassMethod::set_method_name(const std::string& newName){
  this->ClassMethodName = newName;
}

const std::list <std::string> ClassMethod::get_parameters() const{
    return this->ClassParameters;
}

bool ClassMethod::add_parameter(const std::string& paramName){
    if(does_parameter_exist(paramName))
    {
        return false;
    }
    else
    {
        ClassParameters.push_back(paramName);
        return true;
    }
}

bool ClassMethod::remove_parameter(const std::string& paramName){

  auto i = get_param_iter_by_name(paramName);

      if(i == ClassParameters.end())
    {
        return false;
    }
    else
    {
        ClassParameters.erase(i);
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
        (*i).set_param_name(nameTo);
        return true;
    }
}

