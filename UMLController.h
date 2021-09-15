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

        vector<string> Relships;
  
        vector<string> Classes;
        
        UMLModel Model;
        //Helper Prototypes

        bool continuePrompt(string commandLine);

        long unsigned int searchVectorIndex(string input, vector<string> collection);

        bool searchVector(string input, vector<string> collection);

        string sourceParse(string relship);

        string destParse(string relship, long unsigned int index);

        bool search_in_relship(string Class, int option);

    public:
        UMLController(/* args */);
        UMLController(UMLModel newModel);
        ~UMLController();
        

        void execute();

        void print_command_list();

        void list_classes();

        void listRelationships();

        void createClass();

        void createRelationship();

        void deleteClass();

        void deleteRelationship();
};


#endif