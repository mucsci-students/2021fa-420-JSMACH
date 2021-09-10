#include "JSONFileSys.h"
#include "UMLClass.h"
#include "UMLRelationship.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

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
}