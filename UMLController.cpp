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
    else if(userInput == "rename_class")
      rename_class();
    else if(userInput == "edit_attributes")
      edit_attributes();
    else if(userInput == "load")
      load_json();
    else if(userInput == "save")
      save_json();
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
    << "list_classes        : Lists all classes the user has created, as well as their attributes.\n\n"
    << "list_relationships  : Lists all relationships created by the user. (e.g. [source -> destination])\n\n"
    << "create_class        : User will be prompted to name the class, and then it\'ll be created.\n\n"
    << "create_relationship : User will be prompted to type in a source class and a destination class.\n\n"
    << "delete_class        : User will be prompted to type the name of the class they\'d like to delete.\n\n"
    << "delete_relationship : User will be prompted to type the source and destination. The relationship\n"
    << "                      will be no more, but the classes will still exist.\n\n"
    << "rename_class        : User will be prompted to type the existing class name, and then the new\n"
    << "                      name.\n\n"
    << "edit_attributes     : User will be sent to a sub-menu, where they can enter in attribute editor\n"
    << "                      commands.\n\n"
    << "load                : User will be prompted to type the name of the json file, and then it loads\n"
    << "                      the model from that file. WARNING! Existing progress will be overwritten!\n\n"
    << "save                : User will be prompted to name the JSON file, which will contain their\n"
    << "                      current progress.\n\n"
    << "quit                : Exit your current session.\n\n"
    << "exit                : Exit your current session.\n\n";
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
    UMLClass currentClass;
    for(auto iter = classList.begin(); iter != classList.end(); iter++)
    {
      cout << "--> " << (*iter) << "\n";
      
      if (!Model.get_class_by_name(*iter, currentClass))
      {
        cout << "Error! Could not retrieve class by name.\n";
        return;
      }
      vector<UMLAttribute> attributeList = currentClass.get_all_attributes();

      for (int i = 0; i < attributeList.size(); i++)
      {
        cout << "    : " << attributeList[i].get_attribute_name() << "\n";
      }
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
      cout << "SOURCE: \n" << "\t" << currentRel.get_src_class().get_class_name() << std::endl;
      cout << "DESTINATION: \n" << "\t" << currentRel.get_dest_class().get_class_name() << std::endl;
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
  while(!(cin >> attributeCount))
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input.  Try again (input a number): ";
  }

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
    cout << "There are less than two classes in the currently running program. Please add at least two classes. Aborting. " << std::endl;
    return;
  }

  string sourceClassName;
  string destinationClassName;
  UMLClass srcClass;
  UMLClass destClass;
  bool srcValid = false;
  bool destValid = false;

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
  
  if(Model.does_relationship_exist(sourceClassName, destinationClassName))
  {
    cout << "A relationship already exists between " << sourceClassName << " and " << destinationClassName << ". Aborting." << std::endl;
    return;
  }

  if(Model.add_relationship(srcClass, destClass))
    cout << "Add successful!" << std::endl;
  else
    cout << "Adding somehow failed." << std::endl;
}

/*************************/

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

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::delete_relationship()
{
  string sourceClassName;
  string destinationClassName;

  cout << "Enter the source of the relationship to be deleted: " << std::endl;
  cin >> sourceClassName;

  cout << "Enter the destination of the relationship to be deleted: " << std::endl;
  cin >> destinationClassName;

  if(Model.remove_relationship(sourceClassName, destinationClassName))
  {
    cout << "Relationship was successfully deleted" << std::endl;
  }
  else
  {
    cout << "Relationship name did not exist. Aborting." << std::endl;
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

  cout << "Enter the CURRENT name of the class you\'d like to rename. -> ";
  cin >> oldClassName;

  if (!Model.does_class_exist(oldClassName))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }

  cout << "Enter the new name you\'d like to rename it to. -> ";
  cin >> newClassName;
  

  if(!Model.modify_class_name(oldClassName, newClassName))
  {
    cout << "Name modification failed. Make sure the name you typed is a valid class\n"
    << "name, and isn\'t the same name as another class.\n";
    return;
  }
  cout << "The class \"" << oldClassName << "\" has been renamed to \"" << newClassName << "\".\n";
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

  cout << "Enter the name of the class whose attributes you\'d like to edit. -> \n";
  cin >> className;

  if (!Model.does_class_exist(className))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }

  cout << "Type \"help\" to view all available editor commands.\n";
  do
  {
    cout << "-> ";

    cin >> input;
    
    if(input == "help")
      print_attribute_commands();
    
    else if(input == "view")
      list_attributes(className);
    
    else if(input == "add")
      add_attribute(className);
    
    else if(input == "delete")
      delete_attribute(className);
    
    else if(input == "rename")
      rename_attribute(className);
    
    else if(input == "exit")
    {
      cout << "You have exited the attribute editor.\n";
      return;
    }
    else
      cout << "Invadid command! Type \"help\" to view all available attribute editor commands.\n";
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
  cout  << "Enter the name of the JSON file you\'d like to load. -> ";
  cin >> fileName;

  cout << "WARNING! Existing save data will be overwritten. Do you wish to proceed?(y/n) ->";
  
  do
  {
    cin >> answer;
    if(answer != "y" && answer != "n")
      cout << "That was not y/n ";
  } while(answer != "y" && answer != "n");

  if(answer == "n")
    return;
    
  cout << "Attempting to load JSON file...\n";
  if (!Model.load_model_from_json(fileName))
  {
    cout << "Loading failed! The JSON file you typed either does not exist, or is invalid.\n";
    return;
  }

  cout << "Loading complete!\n";
}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::save_json()
{
  string fileName;
  cout << "Type a name for your JSON file.\n"
  << "WARNING! Typing a file name that already exists will automatically overwrite that file.\n-> ";
  
  cin >> fileName;

  // This is for when the model function becomes a bool
  /*
  if(!Model.save_model_to_json(fileName))
  {
    cout << "Invalid file name!\n";
    return;
  }*/
  
  //This call will be deleted once the model function becomes a bool
  Model.save_model_to_json(fileName);
  
  cout << "Your progress was saved to" << fileName << ".json\n";
}
/***********************************************************/
//Helper Functions

/**
 * @brief 
 * 
 */
void UMLController::print_attribute_commands()
{
  cout << "ATTRIBUTE EDITOR COMMANDS:\n"
    << "view   : View the current class with its attributes.\n"
    << "add    : Add a new attribute.\n"
    << "delete : Delete an existing attribute.\n" 
    << "rename : Rename an existing attribute.\n"
    << "exit   : Quit the attribute editor and return to the normal interface.\n\n";
}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::list_attributes(string className)
{
  cout << "--> " << className << "\n";
  UMLClass modelClass;
  Model.get_class_by_name(className, modelClass);
  vector<UMLAttribute> attributeList = modelClass.get_all_attributes();

  for (int i = 0; i < attributeList.size(); i++)
  {
    cout << "    : " << attributeList[i].get_attribute_name() << "\n";
  }

}

/*************************/

void UMLController::add_attribute(string className)
{
  string attName;
  cout << "Type a name for the attribute you\'d like to add. -> ";
  cin >> attName;

  UMLAttribute newAttribute {attName};
  

  if(!Model.add_class_attribute(className, newAttribute))
  {
    cout << "Error! Could not add new attribute.\n";
    return;
  }

  cout << "You have added the attribute \"" << attName << "\" to the class \"" << className << "\".\n";
}

/*************************/

void UMLController::delete_attribute(string className)
{
  string attName;
  cout << "Type the name of the attribute you\'d like to delete. -> ";
  cin >> attName;

  if(!Model.remove_class_attribute(className, attName))
  {
    cout << "Error! Could not delete attribute.\n";
    return;
  }
  cout << "The attribute \"" << attName << "\" was deleted.\n";
}

/*************************/

void UMLController::rename_attribute(string className)
{
  string attNameFrom;
  string attNameTo;

  cout << "Type the name of the attribute you'd like to rename FROM -> ";
  cin >> attNameFrom;
  cout << "Type the name of the attribute you'd like to rename TO -> ";
  cin >> attNameTo; 

  if(!Model.remove_class_attribute(className, attNameFrom))
  {
    cout << "Error! Attribute was not found on the class " << className << "\n";
    return;
  }

  if(!Model.add_class_attribute(className, attNameTo))
  {
    cout << "Error! Attribute could not be added to " << className << "\n";
    return;
  }

  cout << "Attribute successfully renamed" << std::endl;
}
