#include "UMLModel.h"

UMLModel::UMLModel() {}

UMLModel::~UMLModel(){}

std::list<UMLClass>::iterator UMLModel::get_class_iter_by_name(std::string className)
{
    if(AllClasses.empty())
        return AllClasses.end();

    for(auto iter = AllClasses.begin(); iter != AllClasses.end(); iter++)
    {
        if((*iter).get_class_name() == className)
            return iter;
    }

    return AllClasses.end();
}

bool UMLModel::does_class_exist(std::string className)
{
    return get_class_iter_by_name(className) != AllClasses.end();
}

bool UMLModel::add_class(std::string className)
{
    if(does_class_exist(className))
    {
        return false;
    }
    else
    {
        UMLClass newClass {className};
        AllClasses.push_back(newClass);
        return true;
    }
}

bool UMLModel::add_class(std::string className, std::vector<UMLAttribute> attributes)
{
    if(does_class_exist(className))
    {
        return false;
    }
    else
    {
        UMLClass newClass {className, attributes};
        AllClasses.push_back(newClass);
        return true;
    }
}

bool UMLModel::remove_class(std::string className)
{
    auto iter = get_class_iter_by_name(className);

    if(iter == AllClasses.end())
    {
        return false;
    }
    else
    {
        AllClasses.erase(iter);
        return true;
    }
}

bool UMLModel::modify_class_name(std::string nameFrom, std::string nameTo)
{
    // If the name we're modifying to exists already OR the name we're modifying 
    // from doesn't exist, return false
    if(does_class_exist(nameTo) || !does_class_exist(nameFrom))
    {
        return false;
    }
    else
    {
        auto iter = get_class_iter_by_name(nameFrom);
        (*iter).set_class_name(nameTo);
        return true;
    }
}

const std::list <std::string> UMLModel::get_all_class_names()
{
    std::list <std::string> result;

    for (auto c : AllClasses)
    {
        result.push_back(c.get_class_name());
    }

    return result;
}