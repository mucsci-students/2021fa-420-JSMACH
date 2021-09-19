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

        void print_attribute_commands();

        void list_attributes(UMLClass theClass);
        
        void add_attribute(UMLClass &outClass);

        void delete_attribute(UMLClass &outClass);

        void rename_attribute(UMLClass &outClass);

        // The view will also eventually go here
        
    public:
        UMLController();
        UMLController(UMLModel newModel);
        ~UMLController();
    
        // Takes in user input and calls different functions based on
        // what command the user typed.
        void execute();

        //prints the list of all user commands to be typed in execute()
        void print_command_list();

        //Lists all classes the user has created.
        void list_classes();

        //Lists all relationships the user has created.
        void list_relationships();

        void create_class();

        void create_relationship();

        void delete_relationship();

        void delete_class();

        void rename_class();

        void edit_attributes();
  
        void load_json();

        void save_json();

};


#endif