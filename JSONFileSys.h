#ifndef JSON_FILE_SYS
#define JSON_FILE_SYS

#include "UMLClass.h"
#include "UMLRelationship.h"
#include "UMLModel.h"
#include <string>
#include <list>


class JSONFileSys {
    public:
        // Saves the model object passed in as a json file to the project root directory.
        // fileName is the desired name of the file, and will append .json on the end to whatever
        // is passed in to ensure it is the correct format.
        void save_current_model(std::string fileName, UMLModel currentModel);

        // Loads a model object passed in as a reference from the json file in the root directory saved as fileName.json
        // .json is appended to filename to ensure the format. Returns true if the load was successful, false otherwise. 
        //
        // Failure to load could occur for a variety of reasons.
        // For example, if the fileName.json file does not exist in the project root, or if the json file attempting
        // to be loaded would violate the UMLModel's rules (ie, dupliate classes, attributes, etc)
        //
        // NOTE as of 9/13, the model does not validate that the json is valid before loading it.
        bool load_current_model(std::string fileName, UMLModel& currentModel);
};

#endif