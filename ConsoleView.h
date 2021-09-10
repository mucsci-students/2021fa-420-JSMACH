#ifndef UML_CONSOLE_VIEW
#define UML_CONSOLE_VIEW
#include <string>
#include "UMLAttribute.h"
#include "UMLClass.h"
#include "UMLRelationship.h"
#include <vector>
#include <list>


/*
    The ConsoleView is responsible for displaying information to the user.
    Very little if any application logic is handled in the view class.
*/
class ConsoleView
{

public:
    ConsoleView(){};
  
    void UserInputLoop(){}  
    
    
    // PrintClass Name will be used to Print the names of the class being passed by the user
    //@ Para: UMLClass object 
    void PrintClassName(UMLClass X){}
    
    //PrintClass Attribute will Print a List of Attributes which are stored in the specified class
    //@Para: UMLClass Object  
    void PrintClassAttribute(UMLClass X){}
    
    //PrintClassRelations will Print the current list of Relationships the class being passed has
    //@para: UmlClass Obj
    void PrintClassRelations(UMLClass X){}
    
    //PrintListofClass will Print out the list of classes currently in the Model
    //@para: list<string> 
    void PrintAllClasses(std::list<std::string> x){}
        
  
  
};


#endif
