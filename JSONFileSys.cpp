#include "JSONFileSys.h"
#include "UMLClass.h"
#include "UMLRelationship.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>

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
    // Grab the current model classes and relationship data.
    // In case the model attempting to be loaded isn't valid,
    // the data needs to be "put back"
    auto oldClassData = currentModel.AllClasses;
    auto oldRelationshipData = currentModel.AllRelationships;

    try
    {
        std::string saveName = fileName.append(".json");
        std::ifstream ifs(saveName);
        // If the file exists, load the data. Else return false
        if(ifs)
        {
            json data = json::parse(ifs);

            // Ensure classes loaded from json are valid
            std::list <UMLClass> candidateClassList = data["AllClasses"].get<std::list<UMLClass>>();
            if(ensure_json_classes_is_valid(candidateClassList))
            {
                currentModel.AllClasses = candidateClassList;
            }
            else
            {
                ifs.close();
                return false;
            }

            // reinitializing relationships is... complicated...
            json candidateRelationshipJson = data["AllRelationships"];
            
            if(initialize_relationships(candidateRelationshipJson, currentModel))
            {
                ifs.close();
                return true;
            }
            else
            {
                currentModel.AllClasses = oldClassData;
                currentModel.AllRelationships = oldRelationshipData;
                ifs.close();
                return false;
            }
        }
        else
        {
            // Don't bother to reinstate old data; we didn't get to that point
            ifs.close();
            return false;
        }
    }
    catch(...)
    {
        // In the case of an exception, we want to put the old data back for safety
        currentModel.AllClasses = oldClassData;
        currentModel.AllRelationships = oldRelationshipData;
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

bool JSONFileSys::initialize_relationships(json candidateRelationshipJson, UMLModel& currentModel)
{
    for (json::iterator it = candidateRelationshipJson.begin(); it != candidateRelationshipJson.end(); ++it)
    {
        json j = *it;
        std::string classSrcName = j["ClassSrc"];
        std::string classDestName = j["ClassDest"];

        if(!currentModel.add_relationship(classSrcName, classDestName))
        {
            return false;
        }
    }
    
    return true;
}