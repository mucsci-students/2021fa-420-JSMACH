/**
 * @file UMLController.cpp
 * @author Matt Giacoponello, Joshua Carney
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************/
//Notes & Personal Reminders 




/***********************************************************/
//include statements

#include "UMLController.h"
#include "UMLException.hpp"
#include <iostream>
#include <vector>
#include <string.h>


/***********************************************************/
//Using declarations

using std::string;

using std::cin; //Temporary

using std::vector;
using std::list;


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

void UMLController::execute()
{

  string userInput; 

  do
  {
    userInput = Interface.console_menu();

    //Checks for different commands
    /*if (userInput == "help")
    {
      string help = command_list();
      Interface.display_message(help);
    }

    else */if(userInput == "list_classes")
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
    
    else if(userInput == "rename_class")
      rename_class();
    
    else if(userInput == "edit_attributes")
      edit_attributes();
    
    else if(userInput == "load")
      load_json();
    
    else if(userInput == "save")
      save_json();
    
    else if (userInput == "quit")
      cout << "\n";
    
    else
    {
      Interface.display_message("Invalid command! Type \"help\" to view all available coommands.\n");
    }
  }
  while(userInput != "quit");
  
  Interface.display_message("See ya!\n");
}

/*************************/

/**
 * @brief Stores the list of all available commands, except for "help",
 * because let's be real here, if they didn't already know that, they
 * wouldn't have gotten here in the first place. XD
 * 
 */
/*string UMLController::command_list()
{
  //Sorry. The compiler made me do it like this. X'D
  string commandList = "COMMANDS:\n\n" + "list_classes        : Lists all classes the user has created, as well as their attributes.\n\n" + "list_relationships  : Lists all relationships created by the user. (e.g. [source -> destination])\n\n" + "create_class        : User will be prompted to name the class, and then it\'ll be created.\n\n" + "create_relationship : User will be prompted to type in a source class and a destination class.\n\n" + "delete_class        : User will be prompted to type the name of the class they\'d like to delete.\n\n" + "delete_relationship : User will be prompted to type the source and destination. The relationship\n" + "                      will be no more, but the classes will still exist.\n\n" + "rename_class        : User will be prompted to type the existing class name, and then the new\n" + "                      name.\n\n" + "edit_attributes     : User will be sent to a sub-menu, where they can enter in attribute editor\n" + "                      commands.\n\n" + "load                : User will be prompted to type the name of the json file, and then it loads\n" + "                      the model from that file. WARNING! Existing progress will be overwritten!\n\n" + "save                : User will be prompted to name the JSON file, which will contain their\n" + "                      current progress.\n\n" + "quit                : Exit your current session.\n\n";

  return commandList;
}

/*************************/

/**
 * @brief Lists all classes the user has created.
 * 
 */
void UMLController::list_classes()
{
  list<string> classList = Model.get_all_class_names();

  //if no classes, error message.
  if (classList.size() == 0)
  {
    Interface.display_message("You have no classes.\n");
    return;
  }
  
  UMLClass currentClass;

  for(auto iter = classList.begin(); iter != classList.end(); iter++)
  {   
    if (!Model.get_class_by_name(*iter, currentClass))
    {
      Interface.display_message("Error! Could not retrieve class by name.\n");
      return;
    }

    //This function also lists the class.
    list_attributes(*iter);
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
    Interface.display_message("You have no relationships.\n");

  else
  {
    for(auto iter = allRelationships.begin(); iter != allRelationships.end(); iter++)
    {
      UMLRelationship currentRel = *iter;
      string source = currentRel.get_src_class().get_class_name();
      string destination = currentRel.get_dest_class().get_class_name();
      string rType = currentRel.type_to_string();
      Interface.display_relationship(source, destination, rType);
    }
  }
  
}

/*************************/

/**
 * @brief The user is prompted to name the class
 * and then it pushes the class into the vector.
 * 
 */
void UMLController::create_class()
{
  UMLClass newClass;

  string userInputClassName;
  Interface.display_message("Choose a name for your class -> ");
  userInputClassName = Interface.get_user_input();

  if(Model.does_class_exist(userInputClassName))
  {
    Interface.display_message("That class name already exists. Aborting.\n");
    return;
  }

  newClass.set_class_name(userInputClassName);

  int attributeCount; //We should make this unsigned in the future. The reason I'm not doing it now is because the compiler might complain.
  Interface.display_message("How many attributes would you like to start with? -> ");
  
  //Hmmm... I'm not sure how to transfer this to ConsoleView appropriately.
  //-----------------------------------------------------------------------
  while(!(cin >> attributeCount))
  {
    cin.clear();
    cin.ignore(1000, '\n');
    Interface.display_message("Invalid input. Try again (input a number): ");
  }
  //-----------------------------------------------------------------------

  for(int i = 0; i < attributeCount; i++)
  {
    string attributeName;
    Interface.display_message("What would you like to name your attribute? -> ");
    attributeName = Interface.get_user_input();

    UMLAttribute newAttribute {attributeName};
    if(!newClass.add_attribute(newAttribute))
    {
      Interface.display_message("That attribute name was not valid (duplicate attribute)\n");
      i--;
    }
  }

  if(Model.add_class(newClass))
  {
    Interface.display_message("Successfully added new class " + userInputClassName + "\n");
  }
  else
  {
    Interface.display_message("Something went wrong when adding the new class " + userInputClassName + "\n");
  }
}

/*************************/

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
  if(Model.get_all_class_names().size() < 1)
  {
    Interface.display_message("There are less than two classes in the currently running program. Please add at least two classes. Aborting.\n");
    return;
  }

  string sourceClassName;
  string destinationClassName;
  string relationshipType;
  RelationshipType rType;

  bool srcValid = false;
  bool destValid = false;
  bool relationshipTypeValid = false;

  do
  {
    Interface.display_message("Type in a class name you'd like to use for the source -> ");
    sourceClassName = Interface.get_user_input();

    if(!Model.does_class_exist(sourceClassName))
    {
      Interface.display_message("The class \"" + sourceClassName + "\" does not exist.\n");
    }
    else
    {
      srcValid = true;
    }
  } while (!srcValid);
  
  do
  {
    Interface.display_message("Type in a class name you'd like to use for the destination -> ");
    destinationClassName = Interface.get_user_input();
    if(!Model.does_class_exist(destinationClassName))
    {
      Interface.display_message("The class \"" + destinationClassName + "\" does not exist.\n");
    }
    else
    {
      destValid = true;
    }
  } while (!destValid);
  
  if(Model.does_relationship_exist(sourceClassName, destinationClassName))
  {
    Interface.display_message("A relationship already exists between " + sourceClassName + " and " + destinationClassName + ". Aborting.\n");
    return;
  }

  do
  {
    try
    {
      Interface.display_message("Give a type for your new relationship\n");
      Interface.display_message("(Aggregation, Composition, Inheritance, Realization) -> ");
      relationshipType = Interface.get_user_input();

      rType = UMLRelationship::type_from_string(relationshipType);
      relationshipTypeValid = true;
    }
    catch(UMLErrorCode e)
    {
      Interface.display_message(UMLException::error_to_string(e));
      Interface.display_message("\n");
    }
    
  } while (!relationshipTypeValid);
  

  if(Model.add_relationship(sourceClassName, destinationClassName, rType))
    Interface.display_message("Add successful!\n");
  else
    Interface.display_message("Adding somehow failed.\n");
}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::delete_class()
{
  string className;
  Interface.display_message("Enter class name to be deleted -> ");
  className = Interface.get_user_input();
  if(Model.remove_class(className))
  {
    Interface.display_message(className + " was successfully removed.");
  }
  else
  {
    Interface.display_message("Could not find class name \"" + className + "\". Aborting.\n");
  }
}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::delete_relationship()
{
  string sourceClassName;
  string destinationClassName;

  Interface.display_message("Enter the source of the relationship to be deleted -> ");
  sourceClassName = Interface.get_user_input();

  Interface.display_message("Enter the destination of the relationship to be deleted -> ");
  destinationClassName = Interface.get_user_input();

  if(Model.remove_relationship(sourceClassName, destinationClassName))
  {
    Interface.display_message("Relationship was successfully deleted.\n");
  }
  else
  {
    Interface.display_message("Relationship was not found. Aborting.\n");
  }
}

/*************************/

/**
 * @brief 
 * 
 */
void  UMLController::rename_class()
{
  string oldClassName;
  string newClassName;

  Interface.display_message("Enter the CURRENT name of the class you\'d like to rename. -> ");
  oldClassName = Interface.get_user_input();

  if (!Model.does_class_exist(oldClassName))
  {
    Interface.display_message("Error! The class you typed does not exist.\n");
    return;
  }

  Interface.display_message("Enter the new name you\'d like to rename it to. -> ");
  newClassName = Interface.get_user_input();
  

  if(!Model.modify_class_name(oldClassName, newClassName))
  {
    Interface.display_message("Name modification failed. Make sure the name you typed is a valid class\nname, and isn\'t the same name as another class.\n");
    return;
  }
  Interface.display_message("The class \"" + oldClassName + "\" has been renamed to \"" + newClassName + "\".\n");
}







/*************************/

/**
 * @brief 
 * 
 */
void UMLController::edit_attributes()
{
  string className;
  string input;

  Interface.display_message("Enter the name of the class whose attributes you\'d like to edit.\n-> ");
  className = Interface.get_user_input();

  if (!Model.does_class_exist(className))
  {
    Interface.display_message("Error! The class you typed does not exist.\n");
    return;
  }

  Interface.display_message("Type \"help\" to view all available editor commands.\n");
  do
  {
    Interface.display_message("-> ");

    input = Interface.attribute_menu();
    
    /*if(input == "help")
      print_attribute_commands();
    
    else */if(input == "view")
      list_attributes(className);
    
    else if(input == "add")
      add_attribute(className);
    
    else if(input == "delete")
      delete_attribute(className);
    
    else if(input == "rename")
      rename_attribute(className);
    
    else if(input == "exit")
    {
      Interface.display_message("You have exited the attribute editor.\n");
      return;
    }
    else
      Interface.display_message("Invadid command! Type \"help\" to view all available attribute editor commands.\n");
  }
  while(1);

}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::load_json()
{
  string fileName;
  string answer;
 
  Interface.display_message("Enter the name of the JSON file you\'d like to load. -> ");
  fileName = Interface.get_user_input();
  Interface.display_message("WARNING! Existing save data will be overwritten. Do you wish to proceed? (y/n) -> ");
  
  do
  {
    answer = Interface.get_user_input();
    if(answer != "y" && answer != "n")
      Interface.display_message("That was not y/n\n");
  } while(answer != "y" && answer != "n");

  if(answer == "n")
    return;
    
  Interface.display_message("Attempting to load JSON file...\n");
  if (!Model.load_model_from_json(fileName))
  {
    Interface.display_message("Loading failed! The JSON file you typed either does not exist, or is invalid.\n");
    return;
  }

  Interface.display_message("Loading complete!\n");
}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::save_json()
{
  string fileName;
  Interface.display_message("Type a name for your JSON file.\nWARNING! Typing a file name that already exists will automatically overwrite that file.\n-> ");
  
  fileName = Interface.get_user_input();

  // This is for when the model function becomes a bool
  /*
  if(!Model.save_model_to_json(fileName))
  {
    Interface.display_message("Invalid file name!\n");
    return;
  }*/
  
  //This call will be deleted once the model function becomes a bool
  Model.save_model_to_json(fileName);
  
  Interface.display_message("Your progress was saved to " + fileName + ".json\n");
}





/***********************************************************/
//Helper Functions

/**
 * @brief 
 * 
 */
/*void UMLController::print_attribute_commands()
{
  Interface.display_message("ATTRIBUTE EDITOR COMMANDS:\n" + "view   : View the current class with its attributes.\n" + "add    : Add a new attribute.\n" + "delete : Delete an existing attribute.\n" + "rename : Rename an existing attribute.\n" + "exit   : Quit the attribute editor and return to the normal interface.\n\n");
}*/

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::list_attributes(string className)
{
  Interface.display_class(className);
  UMLClass modelClass;
  Model.get_class_by_name(className, modelClass);
  vector<UMLAttribute> attributeList = modelClass.get_all_attributes();

  for (int i = 0; i < attributeList.size(); i++)
  {
    Interface.display_attribute(attributeList[i].get_attribute_name());
  }

}

/*************************/

void UMLController::add_attribute(string className)
{
  string attName;
  Interface.display_message("Type a name for the attribute you\'d like to add. -> ");
  attName = Interface.get_user_input();

  UMLAttribute newAttribute {attName};
  

  if(!Model.add_class_attribute(className, newAttribute))
  {
    Interface.display_message("Error! Could not add new attribute.\n");
    return;
  }

  Interface.display_message("You have added the attribute \"" + attName + "\" to the class \"" + className + "\".\n");
}

/*************************/

void UMLController::delete_attribute(string className)
{
  string attName;
  Interface.display_message("Type the name of the attribute you\'d like to delete. -> ");
  attName = Interface.get_user_input();

  if(!Model.remove_class_attribute(className, attName))
  {
    Interface.display_message("Error! Could not delete attribute.\n");
    return;
  }
  Interface.display_message("The attribute \"" + attName + "\" was deleted.\n");
}

/*************************/

void UMLController::rename_attribute(string className)
{
  string attNameFrom;
  string attNameTo;

  Interface.display_message("Type the name of the attribute you'd like to rename FROM -> ");
  attNameFrom = Interface.get_user_input();
  Interface.display_message("Type the name of the attribute you'd like to rename TO -> ");
  attNameTo = Interface.get_user_input(); 

  if(!Model.remove_class_attribute(className, attNameFrom))
  {
    Interface.display_message("Error! Attribute was not found on the class \"" + className + "\".\n");
    return;
  }

  if(!Model.add_class_attribute(className, attNameTo))
  {
    Interface.display_message("Error! Attribute could not be added to \"" + className + "\".\n");
    return;
  }

  Interface.display_message("Attribute successfully renamed.\n");
}
