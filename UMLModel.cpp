#include "UMLModel.h"
#include "JSONFileSys.h"

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

bool UMLModel::add_class(UMLClass newClass)
{
    if(does_class_exist(newClass.get_class_name()))
    {
        return false;
    }
    else
    {
        AllClasses.push_back(newClass);
        return true;
    }
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
        ensure_relationship_delete(className);
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
        modify_relationship(nameFrom, nameTo);
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

std::list<UMLRelationship>::iterator UMLModel::get_relationship_iter_by_src_and_dest_name(std::string classSrc, std::string classDest)
{
    if(AllRelationships.empty())
    {
        return AllRelationships.end();
    }

    for(auto i = AllRelationships.begin(); i != AllRelationships.end(); i++)
    {
        if((*i).get_src_class().get_class_name() == classSrc 
            && (*i).get_dest_class().get_class_name() == classDest)
        {
            return i;
        }
    }

    return AllRelationships.end();
}
 
bool UMLModel::does_relationship_exist(std::string classSrc, std::string classDest)
{
    return get_relationship_iter_by_src_and_dest_name(classSrc, classDest) != AllRelationships.end();
}

bool UMLModel::add_relationship(UMLClass src, UMLClass dest)
{
    if(does_relationship_exist(src.get_class_name(), dest.get_class_name()))
    {
        return false;
    }
    else
    {
        if (does_class_exist(src.get_class_name()) && does_class_exist(dest.get_class_name()))
        {
            UMLRelationship newRelationship {src, dest};
            AllRelationships.push_back(newRelationship);
            return true;
        }
        else
        {
            return false;
        }
    }
}

 bool UMLModel::remove_relationship(std::string classSrc, std::string classDest)
 {
     auto i = get_relationship_iter_by_src_and_dest_name(classSrc, classDest);
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

 const std::list <UMLRelationship> UMLModel::get_class_relationships(std::string className)
 {
     std::list <UMLRelationship> result;

     if (does_class_exist(className))
     {
         for (auto i = AllRelationships.begin() ; i != AllRelationships.end() ; i++)
         {
             if ((*i).get_src_class() == className || (*i).get_dest_class() == className)
             {
                 result.push_back(*i);
             }
         }
     }
     return result;
}

const std::list <UMLRelationship> UMLModel::get_all_relationships()
{
    return AllRelationships;
}

void UMLModel::ensure_relationship_delete(std::string className)
{
    std::list <UMLRelationship> classRelats = get_class_relationships(className);
    
    for (auto i = classRelats.begin() ; i != classRelats.end() ; i++)
    {
        remove_relationship((*i).get_src_class().get_class_name(), (*i).get_dest_class().get_class_name());
    }
}

bool UMLModel::get_relationship_by_src_and_dest(std::string classSrc, std::string classDest, UMLRelationship& outRelationship)
{
    if(does_relationship_exist(classSrc, classDest))
    {
        outRelationship = *(get_relationship_iter_by_src_and_dest_name(classSrc, classDest));
        return true;
    }
    else
    {
        return false;
    }
}

void UMLModel::modify_relationship(std::string nameFrom, std::string nameTo)
{
    std::list <UMLRelationship> classRelats = get_class_relationships(nameFrom);
    for (auto i = classRelats.begin() ; i != classRelats.end() ; i++)
        {
            if ((*i).get_src_class().get_class_name() == nameFrom)
            {
                (*i).get_src_class().set_class_name(nameTo);
            }
            if ((*i).get_dest_class().get_class_name() == nameFrom)
            {
                (*i).get_dest_class().set_class_name(nameTo);
            }
        }
}

bool UMLModel::get_class_by_name(std::string className, UMLClass& outClass)
{
    if(does_class_exist(className))
    {
        outClass = *(get_class_iter_by_name(className));
        return true;
    }
    else
    {
        return false;
    }
}

bool UMLModel::add_class_attribute(std::string className, UMLAttribute attribute)
{
    UMLClass existingClass;
    if(get_class_by_name(className, existingClass))
    {
        if(existingClass.add_attribute(attribute))
        {
            return true;
        }
    }

    return false;
}

bool UMLModel::remove_class_attribute(std::string className, std::string attributeName)
{
    UMLClass existingClass;
    if(get_class_by_name(className, existingClass))
    {
        if(existingClass.remove_attribute(attributeName))
        {
            return true;   
        }
    }

    return false;
}

void UMLModel::save_model_to_json(std::string fileName)
{
    JSONFileSys jsonIO;
    jsonIO.save_current_model(fileName, *this);
}

bool UMLModel::load_model_from_json(std::string fileName)
{
    JSONFileSys jsonIO;
    return jsonIO.load_current_model(fileName, *this);
}
