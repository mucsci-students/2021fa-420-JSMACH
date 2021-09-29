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
//#include "IView.h"
#include "ConsoleView.h" //temporary

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
    //IView Interface; - This will be uncommented once the IView is complete.
    
    ConsoleView Interface; // This is temporary

    //void print_attribute_commands();

    void list_attributes(string className);
        
    void add_attribute(string className);

    void delete_attribute(string className);

    void rename_attribute(string className);


    // The view will also eventually go here
        
  public:
    UMLController();
    UMLController(UMLModel newModel);
    ~UMLController();
    
    // Takes in user input and calls different functions based on
    // what command the user typed.
    void execute();

    // Returns a string of all available commands for the user to
    // type in the command line, or click in the GUI.
    //string command_list();

    // Lists all classes the user has created.
    void list_classes();

    // Lists all relationships the user has created.
    void list_relationships();

    // User creates and names a class and may give it any number
    // of attributes.
    void create_class();

    // Creates a new relationship between classes.
    void create_relationship();

    // User will be prompted to type in the class name,
    // and if it exists, it will be deleted.
    void delete_class();

    // User will be prompted to type in the source and destination,
    // and if the relationship exists, it will be deleted.
    void delete_relationship();

    // User types in the current class name, and then the name
    // they'd like to change it to. Then it gets renamed.
    void rename_class();

    // Does various things with attributes based on user input.
    void edit_attributes();

    // Loads a json save file, overwriting the current session.
    void load_json();

    // Saves the user's progress into a json file.
    void save_json();

};


#endif