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
    void Print_Class_Name(UMLClass X);
    
    //PrintClass Attribute will Print a List of Attributes which are stored in the specified class
    //@Para: UMLClass Object  
    void Print_Class_Attribute(UMLClass X);
    
    //PrintClassRelations will Print the current list of Relationships the class being passed has
    //@para: UmlClass Obj
    void Print_Class_Relations(UMLRelationship X);
    
    //PrintListofClass will Print out the list of classes currently in the Model
    //@para: list<string> 
    void Print_All_Classes(std::list<std::string> x);
    
    
    //Print The current Soruce and Dest of the Relationship 
    //@para: UMLRelationship obj
    void Print_Source_and_Dest(UMLRelationship x);

    //Print All the classes stored in the model
    //@para: UMLMODEL
    void Print_All_Classes(UMLModel x);

    
  
  
};


#endif
