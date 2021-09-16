#include "JSONFileSys.h"
#include "UMLClass.h"
#include "UMLRelationship.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

JSONFileSys::JSONFileSys()
{}

JSONFileSys::~JSONFileSys()
{}

void JSONFileSys::save_current_model(std::string fileName, UMLModel currentModel)
{
    std::string saveName = fileName.append(".json");
    std::list <UMLClass> currentClasses = currentModel.AllClasses;
    std::list <UMLRelationship> currentRelationships = currentModel.AllRelationships;

    json newJsonSave;
    newJsonSave["AllClasses"] = currentClasses;
    newJsonSave["AllRelationships"] = currentRelationships;

    std::ofstream file(fileName);
    file << newJsonSave;
    file.close();
}

bool JSONFileSys::load_current_model(std::string fileName, UMLModel& currentModel)
{
    try
    {
        std::string saveName = fileName.append(".json");
        std::ifstream ifs(saveName);
        // If the file exists, load the data. Else return false
        if(ifs)
        {
            json data = json::parse(ifs);

            std::list <UMLClass> candidateClassList = data["AllClasses"].get<std::list<UMLClass>>();
            std::list <UMLRelationship> candidateRelationshipList = data["AllRelationships"].get<std::list<UMLRelationship>>();

            if(ensure_json_classes_is_valid(candidateClassList) 
                && ensure_json_relationships_is_valid(candidateRelationshipList))
            {
                currentModel.AllClasses = candidateClassList;
                currentModel.AllRelationships = candidateRelationshipList;
                return true;
            }
            else
            {
                ifs.close();
                return false;
            }
        }
        else
        {
            ifs.close();
            return false;
        }
    }
    catch(...)
    {
        return false;
    }
    return false;
}

bool JSONFileSys::ensure_json_classes_is_valid(std::list <UMLClass> candidateClassList)
{
    // Iterate through each class in the list
    for(auto iter = candidateClassList.begin(); iter != candidateClassList.end(); iter++)
    {
        std::string currentClassName = (*iter).get_class_name();
        int count = 0;
        // Iterate through the list and see if the name of the current class matches any of the others
        // Valid models should only have ONE class name. If the count of class names is >1, return false.
        for(auto classIter = candidateClassList.begin(); classIter != candidateClassList.end(); classIter++)
        {
            if((*classIter).get_class_name() == currentClassName)
                count++;
        }
        if(count > 1)
            return false;
    }

    return true;
}

bool JSONFileSys::ensure_json_relationships_is_valid(std::list <UMLRelationship> candidateRelationshipList)
{
    // Iterate through each relationship in the list
    for(auto iter = candidateRelationshipList.begin(); iter != candidateRelationshipList.end(); iter++)
    {
        std::string currentRelationshipName = (*iter).get_relationship_name();
        int count = 0;
        // Iterate through the list and see if the name of the current relationship matches any of the others
        // Valid models should only have ONE relationship name. If the count of relationship names is >1, return false.
        for(auto relIter = candidateRelationshipList.begin(); relIter != candidateRelationshipList.end(); relIter++)
        {
            if((*relIter).get_relationship_name() == currentRelationshipName)
                count++;
        }
        if(count > 1)
            return false;
    }

    return true;
}