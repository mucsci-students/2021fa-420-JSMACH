/**
 * @file UMLController.cpp
 * @author Matt Giacoponello
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************/
//include statements

#include "UMLController.h"
#include <iostream>
#include <vector>
#include <string.h>


/***********************************************************/
//Using declarations

using std::string;
using std::cout;
using std::cin;
using std::vector;


/***********************************************************/
//Structs & Global Variables 



/***********************************************************/
//Constructor

UMLController::UMLController()
{}

UMLController::UMLController(UMLModel newModel)
  : Model(newModel)
{}

UMLController::~UMLController()
{}

/***********************************************************/
//Functions
/***********************************************************/


/**
 * @brief Takes in user input and does string comparisons to see if the user typed
 * in a valid command, and does different things based on which command was typed.
 * 
 * 
 */
void UMLController::execute()
{
  cout << "Type \"help\" for the list of commands.\n";
  cout << "Type \"exit\" to quit your current session.\n";

  string userInput;

  do 
  {
    
    cout << "> ";
    cin >> userInput;

    //Checks for different commands
    if (userInput == "help")
      print_command_list();

    else if(userInput == "list_classes")
      list_classes();
    
    else if(userInput == "list_relationships")

      list_relationships();
    
    else if(userInput == "create_class")
      create_class();
    
    else if(userInput == "create_relationship")
      create_relationship();

    else if(userInput == "delete_class")
      delete_class();
      
    else if(userInput == "delete_relationship")
      delete_relationship();

    else if (userInput == "exit")
      cout << "\n";
    else
    {
      cout << "Invadid command! Type \"help\" to view all available commands.\n";
    }

  } while (userInput != "exit");
  
  //This is when the user quits their current session. But I figured I'd make it a little more interesting...  >:D
  cout << "See ya\n";
}

/*************************/

/**
 * @brief Prints the list of all available commands, except for "help",
 * because let's be real here, if they didn't already know that, they
 * wouldn't have gotten here in the first place. XD
 * 
 */
void UMLController::print_command_list()
{
  cout << "COMMANDS:\n\n" 
    << "list_classes        : Lists all classes the user has created.\n"
    << "list_relationships  : Lists all relationships created by the user. (e.g. [source -> destination])\n"
    << "create_class        : User will be prompted to name the class, and then it\'ll be created.\n"
    << "create_relationship : User will be prompted to type in a source class and a destination class.\n"
    << "delete_class        : User will be prompted to type the name of the class they\'d like to delete.\n"
    << "delete_relationship : User will be prompted to type the source and destination. The relationship will be no more, but the classes will still exist.\n"
    << "exit                : Exit your current session.\n";
}

/*************************/

/**
 * @brief Lists all classes the user has created.
 * 
 */
void UMLController::list_classes()
{
  std::list<string> classList = Model.get_all_class_names();

  //if no classes, error message.
  if (classList.size() == 0)
    cout << "You have no classes.\n";
  
  //else iterate through the collection of classes and list them all.
  else
  {
    for(auto iter = classList.begin(); iter != classList.end(); iter++)
    {
      cout << "--> " << (*iter) << std::endl;
    }
  }

}

/*************************/

/**
 * @brief Lists all relationships the user has created.
 * 
 */
void UMLController::list_relationships()
{
  std::list <UMLRelationship> allRelationships = Model.get_all_relationships();
  if (allRelationships.size() == 0)
    cout << "You have no relationships.\n";

  else
  {
    for(auto iter = allRelationships.begin(); iter != allRelationships.end(); iter++)
    {
      UMLRelationship currentRel = *iter;
      cout << "NAME: " << currentRel.get_relationship_name() << std::endl;
      cout << "\tSOURCE: " << currentRel.get_src_class().get_class_name() << std::endl;
      cout << "\tDESTINATION: " << currentRel.get_dest_class().get_class_name() << std::endl;
    }
  }
  
}

/**
 * @brief The user is prompted to name the class
 * and then it pushes the class into the vector.
 * 
 */
void UMLController::create_class()
{
  UMLClass newClass;

  string userInputClassName;
  cout << "Choose a name for your class -> ";
  cin >> userInputClassName;

  if(Model.does_class_exist(userInputClassName))
  {
    cout << "That class name already exists. Aborting." << std::endl;
    return;
  }

  newClass.set_class_name(userInputClassName);

  int attributeCount;
  cout << "How many attributes would you like to start with? -> ";
  cin >> attributeCount;
  for(int i = 0; i < attributeCount; i++)
  {
    string attributeName;
    cout << "What would you like to name your attribute? -> ";
    cin >> attributeName;
    UMLAttribute newAttribute {attributeName};
    if(!newClass.add_attribute(newAttribute))
    {
      cout << "That attribute name was not valid (duplicate attribute)" << std::endl;
      i--;
    }
  }

  if(Model.add_class(newClass))
  {
    cout << "Successfully added new class " << userInputClassName << std::endl;
  }
  else
  {
    cout << "Something went wrong when adding the new class " << userInputClassName << std::endl;
  }
}
/**
 * @brief The user is prompted to type in the source name and then the destination.
 * If the user types a name that doesn't exist, they must try again. 
 * 
 * However, if the source name DOES exist and the destination name DOESN'T exist, they
 * only need to try again with the destination.
 * 
 */
void UMLController::create_relationship()
{
  if(Model.get_all_class_names().size() < 2)
  {
    cout << "There are less than two classes in the currently running program. Please add at least two classes. Aborting. " << std::endl;
    return;
  }

  string sourceClassName;
  string destinationClassName;
  string relationshipName;
  UMLClass srcClass;
  UMLClass destClass;
  bool srcValid = false;
  bool destValid = false;
  bool relNameValid = false;

  do
  {
    cout << "Type in a class name you'd like to use for the source -> ";
    cin >> sourceClassName;
    if(!Model.get_class_by_name(sourceClassName, srcClass))
    {
      cout << "No such class " << sourceClassName << std::endl;
    }
    else
    {
      srcValid = true;
    }
  } while (!srcValid);
  
  do
  {
    cout << "Type in a class name you'd like to use for the destination -> ";
    cin >> destinationClassName;
    if(!Model.get_class_by_name(destinationClassName, destClass))
    {
      cout << "No such class " << destinationClassName << std::endl;
    }
    else
    {
      destValid = true;
    }
  } while (!destValid);
  
  do
  {
    cout << "Type in a name for the new relationship between the classes -> ";
    cin >> relationshipName;
    if(Model.does_relationship_exist(relationshipName))
    {
      cout << "Relationship already exists within the program." << std::endl;
    }
    else
    {
      relNameValid = true;
    }
  } while (!relNameValid);
  
  if(Model.add_relationship(relationshipName, srcClass, destClass))
    cout << "Add successful!" << std::endl;
  else
    cout << "Adding somehow failed." << std::endl;
  
}

void UMLController::delete_relationship()
{
  string relationshipName;
  cout << "Enter a relationship name to be deleted: " << std::endl;
  cin >> relationshipName;
  if(Model.remove_relationship(relationshipName))
  {
    cout << "Relationship was successfully deleted" << std::endl;
  }
  else
  {
    cout << "Relationship name did not exist. Aborting." << std::endl;
  }
}

/**
 * @brief 
 * 
 */
void UMLController::delete_class()
{
  string className;
  cout << "Enter class name to be deleted: " << std::endl;
  cin >> className;
  if(Model.remove_class(className))
  {
    cout << className << " was successfully removed." << std::endl;
  }
  else
  {
    cout << "Could not find class name " << className << ". Aborting." << std::endl;
  }
}
