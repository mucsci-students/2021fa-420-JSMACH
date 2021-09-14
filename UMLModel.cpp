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

std::list<UMLRelationship>::iterator UMLModel::get_relationship_iter_by_name(std::string relationshipName){
    if(AllRelationships.empty())
    {
        return AllRelationships.end();
    } 
    else 
    {
        for (auto i = AllRelationships.begin() ; i != AllRelationships.end() ; i++)
        {
            if((*i).get_relationship_name() == relationshipName)
            {
                return i;
            }
        }
        return AllRelationships.end();
    }
}
 
 bool UMLModel::does_relationship_exist(std::String relationshipName)
 {
     return get_relationship_iter_by_name(relationshipName) != AllRelationships.end();
 }

 bool UMLModel::add_relationship(std::String name, UMLClass& src, UMLClass& dest)
 {
     if (does_relationship_exist(name))
     {
        return false;
     } 
     else
     {
         //both source and destination class must exist for relationship to be created
         if (does_class_exist(src) && does_class_exist(dest)){

            UMLRelationship newRelationship {name, src, dest};
            AllRelationships.push_back(newRelationship);
            return true;
         }
         else 
         {
             return false;
         }
     }
     

}

 bool UMLModel::remove_relationship(std::String relationshipName)
 {
     auto i = get_relationship_iter_by_name(relationshipName);
     if (i == AllRelationships.end())
     {
         return false;
     }
     else 
     {
         AllRelationships.erase(i);
         return true;
     }
}

 const std::list <UMLRelationship> UMLModel::get_class_relationships(std::String className)
 {
     std::list <UMLRelationship> result;

     if (does_class_exist(className))
     {
         for (i = AllRelationships.begin() ; i != AllRelationships.end() ; i++)
         {
             if ((*i).get_src_class() == className || (*i).get_dest_class() == className)
             {
                 result.push_back(*i);
             }
         }
     }
     return result;
}