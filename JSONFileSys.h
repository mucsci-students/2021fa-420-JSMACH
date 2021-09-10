#ifndef JSON_FILE_SYS
#define JSON_FILE_SYS

#include "UMLClass.h"
#include "UMLRelationship.h"
#include "UMLModel.h"
#include <string>
#include <list>


class JSONFileSys {
    public:
        void save_current_model(std::string fileName, UMLModel currentModel);
};

#endif