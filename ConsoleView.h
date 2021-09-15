#ifndef UML_CONSOLE_VIEW
#define UML_CONSOLE_VIEW
#include <string>
#include "UMLAttribute.h"
#include "UMLClass.h"
#include "UMLRelationship.h"
#include "UMLModel.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

/*
    The ConsoleView is responsible for displaying information to the user.
    Very little if any application logic is handled in the view class.
*/
class ConsoleView
{

public:
    // PrintClass Name will be used to Print the names of the class being passed by the user
    //@ Para: UMLClass object 
    void print_class_Nname(UMLClass X);
    
    //PrintClass Attribute will Print a List of Attributes which are stored in the specified class
    //@Para: UMLClass Object  
    void print_class_attribute(UMLClass X);
    
    //PrintClassRelations will Print the current list of Relationships the class being passed has
    //@para: UmlClass Obj
    void print_class_relations(UMLRelationship X);
    
    //PrintListofClass will Print out the list of classes currently in the Model
    //@para: list<string> 
    void print_all_classes(std::list<std::string> x);
    
    
    //Print The current Soruce and Dest of the Relationship 
    //@para: UMLRelationship obj
    void [rint_source_and_dest(UMLRelationship x);

    //Print All the classes stored in the model
    //@para: UMLMODEL
    void print_all_classes(UMLModel x);

    
  
  
};


#endif
