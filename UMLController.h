#ifndef UML_CONTROLLER
#define UML_CONTROLLER

/*
    UMLController will be the go between for the model and the view. 
    It will parse the user input, ask the model for the appropriate data, 
    then pass that along to the view.

    Command parsing may want to be relegated to another class instead of here
    as good practice for separation of concerns.
*/

/***********************************************************/
//include statements

#include "UMLModel.h"
#include "UMLRelationship.h"
#include "UMLClass.h"
#include "UMLAttribute.h"
#include <iostream>
#include <vector>
#include <string.h>


/***********************************************************/
//Using declarations

using std::string;
using std::cout;
using std::cin;
using std::vector;

class UMLController
{
    private:
        UMLModel Model;
        // The view will also eventually go here

    public:
        UMLController();
        UMLController(UMLModel newModel);
        ~UMLController();
    

        void execute();

        void print_command_list();

        void list_classes();

        void list_relationships();

        void create_class();

        void create_relationship();

        void delete_relationship();

        void delete_class();

        void rename_class();

        void load_json();

};


#endif