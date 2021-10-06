/**
 * @file UMLController.cpp
 * @author Matt Giacoponello, Joshua Carney, CJ Sydorko
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

  Interface.display_message("Type \"help\" to view all available commands.\nType \"quit\" to quit your current session.\n");
  string userInput; 

  do
  {
    userInput = Interface.console_menu();

    if (userInput == "help")
      Interface.help();

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
    
    else if(userInput == "edit_fields")
      edit_fields();
    
    else if(userInput == "edit_methods")
      edit_methods();
    
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

    Interface.display_class(currentClass);
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

  string className;
  Interface.display_message("Choose a name for your class -> ");
  className = Interface.get_user_input();

  if(Model.does_class_exist(className))
  {
    Interface.display_message("That class name already exists. Aborting.\n");
    return;
  }

  newClass.set_class_name(className);

  if(Model.add_class(newClass))
  {
    Interface.display_message("Successfully added new class \"" + className + "\".\n");
  }
  else
  {
    Interface.display_message("Something went wrong when adding the new class " + className + "\n");
    return;
  }
  
  // This commented out portion will eventually be deleted. But it has pretty much
  // the EXACT same syntax as what you'll be doing for the fields. In fact, if I
  // were you, I'd copy and paste this, and then edit it to say 'field(s)' instead of
  // 'attribute(s)'.

  /*
  Interface.display_message("How many attributes would you like to start with? -> ");
  unsigned int attributeCount = Interface.user_int_input();

  for(int i = 0; i < attributeCount; i++)
  {
    Interface.display_message("What would you like to name your attribute? -> ");
    string attributeName = Interface.get_user_input();

    UMLAttribute newAttribute {attributeName};
    if(!newClass.add_attribute(newAttribute))
    {
      Interface.display_message("That attribute name was not valid (duplicate attribute)\n");
      i--;
    }
  } */

  //--------------------------------------------------------------------
  // TODO
  // Hint: When declaring the field, use the type 'ClassField'
  Interface.display_message("How many fields would you like to start with? -> ");
  unsigned int fieldCount = Interface.user_int_input();



  for(int i = 0; i < fieldCount; i++)
  {
    Interface.display_message("What would you like to name your field? -> ");
    string fieldName = Interface.get_user_input();
    
    ClassField newField {fieldName};

    if(!Model.add_class_field(className, newField))
    {
      Interface.display_message("Error! The field \"" + fieldName + "\" could not be created.\n");
      Interface.display_message("Either the field already exists, or the name is invalid.\n");
      i--;
    } 
    else
    {
      Interface.display_message("The field \"" + fieldName + "\" was successfully created!\n");
    }
  }
  //--------------------------------------------------------------------


  Interface.display_message("How many methods would you like to start with? -> ");
  unsigned int methodCount = Interface.user_int_input();



  for(int i = 0; i < methodCount; i++)
  {
    Interface.display_message("What would you like to name your method? -> ");
    string methodName = Interface.get_user_input();
    
    ClassMethod newMethod {methodName};

    if(!Model.add_class_method(className, newMethod))
    {
      Interface.display_message("Error! The method \"" + methodName + "\" could not be created.\n");
      Interface.display_message("Either the method already exists, or the name is invalid.\n");
      i--;
    } 
    else
    {
      Interface.display_message("The method \"" + methodName + "\" was successfully created!\n");
      Interface.display_message("How many parameters would you like to give this method? -> ");
      unsigned int parameterCount = Interface.user_int_input();
      
      for(int j = 0; j < parameterCount; j++)
      {
        if(!add_parameter(className, methodName))
          j--;
      }
    }
  }

  //For some reason display_class() wasn't successfully retrieving the data until I did this
  if(!Model.get_class_by_name(className, newClass))
  {
    Interface.display_message("Confirmation check somehow failed.\n");
    return;
  }

  Interface.display_message("Overview:\n");
  Interface.display_class(newClass);
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
      relationshipType = Interface.get_relationship_type();

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
 *
void UMLController::edit_attributes()
{
  string className;
  string input;
  UMLClass currentClass;

  Interface.display_message("Enter the name of the class whose attributes you\'d like to edit.\n-> ");
  className = Interface.get_user_input();

  if (!Model.does_class_exist(className))
  {
    Interface.display_message("Error! The class you typed does not exist.\n");
    Interface.display_message("Returning to main menu.\n");
    return;
  }

  Interface.display_message("Type \"help\" to view all available editor commands.\n");
  do
  {
    Interface.display_message("-> ");

    input = Interface.get_user_input();
    
    if(input == "help")
      Interface.print_attribute_commands();
    
    else if(input == "view")
      Interface.display_class(currentClass);
    
    else if(input == "add")
      add_attribute(className);
    
    else if(input == "delete")
      delete_attribute(className);
    
    else if(input == "rename")
      rename_attribute(className);
    
    else if(input == "switch_class")
    {
      //recursive call
      edit_attributes();
      return;
    }
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
 * @brief This method will be extremely similar to the method that's commented
 * out above. Make sure to replace anything that has to do with attributes 
 * with stuff that has to do with fields.
 * 
 * Hint: If the user types "help", call Interface.print_field_commands()
 * 
 */
void UMLController::edit_fields()
{
  string className;
  string input;
  UMLClass currentClass;
  
  Interface.display_message("Enter the name of the class whose fields and/or parameters you\'d like to edit.\n-> ");
  className = Interface.get_user_input();

  if (!Model.does_class_exist(className))
  {
    Interface.display_message("Error! The class you typed does not exist.\n");
    Interface.display_message("Returning to main menu.\n");
    return;
  }
  
  if(!Model.get_class_by_name(className, currentClass))
  {
    Interface.display_message("Error! Could not retrieve class.\n");
    return;
  }

  Interface.display_message("Type \"help\" to view all available editor commands.\n");
  do
  {
    Interface.display_message("-> ");

    input = Interface.get_user_input();
    
    if(input == "help")
      Interface.print_field_commands();
    
    else if(input == "view")
      Interface.display_class(currentClass);
    
    else if(input == "add")
      add_field(className);

    else if(input == "delete")
      delete_field(className);
    
    else if(input == "rename")
      rename_field(className);

    else if (input == "switch_class")
    {
      //recursive call
      edit_fields();
      return;
    }
    else if(input == "exit")
    {
      Interface.display_message("You have exited the field editor.\n");
      Interface.display_message("Returning to main menu.\n");
      return;
    }
    else
      Interface.display_message("Invadid command! Type \"help\" to view all available field editor commands.\n");


    if(!Model.get_class_by_name(className, currentClass))
    {
      Interface.display_message("The changes were successfully made, but failed to update view.\n");
    }
  }
  while(1);

}



/*************************/

/**
 * @brief 
 * 
 */
void UMLController::edit_methods()
{
  string className;
  string input;
  UMLClass currentClass;
  
  Interface.display_message("Enter the name of the class whose methods and/or parameters you\'d like to edit.\n-> ");
  className = Interface.get_user_input();

  if (!Model.does_class_exist(className))
  {
    Interface.display_message("Error! The class you typed does not exist.\n");
    Interface.display_message("Returning to main menu.\n");
    return;
  }
  
  if(!Model.get_class_by_name(className, currentClass))
  {
    Interface.display_message("Error! Could not retrieve class.\n");
    return;
  }

  Interface.display_message("Type \"help\" to view all available editor commands.\n");
  do
  {
    Interface.display_message("-> ");

    input = Interface.get_user_input();
    
    if(input == "help")
      Interface.print_method_commands();
    
    else if(input == "view")
      Interface.display_class(currentClass);
    
    else if(input == "add")
      add_method(className);

    else if(input == "delete")
      delete_method(className);
    
    else if(input == "rename")
      rename_method(className);
    
    else if (input == "edit_parameters")
      edit_parameters(className);

    else if (input == "switch_class")
    {
      //recursive call
      edit_methods();
      return;
    }
    else if(input == "exit")
    {
      Interface.display_message("You have exited the method editor.\n");
      Interface.display_message("Returning to main menu.\n");
      return;
    }
    else
      Interface.display_message("Invadid command! Type \"help\" to view all available method editor commands.\n");


    if(!Model.get_class_by_name(className, currentClass))
    {
      Interface.display_message("The changes were successfully made, but failed to update view.\n");
    }
  }
  while(1);

}

/*************************/

/**
 * @brief 
 * 
 */
void UMLController::edit_parameters(string className)
{
  string methodName;
  string input;
  UMLClass currentClass;

  if (!Model.get_class_by_name(className, currentClass))
  {
    Interface.display_message("Error! Could not retrieve the class by name.\n");
    return;
  }

  Interface.display_message("Enter the name of the method whose parameters you\'d like to edit.\n-> ");
  methodName = Interface.get_user_input();

  if (!Model.does_class_have_method(className, methodName))
  {
    Interface.display_message("Error! The method you typed does not exist.\n");
    Interface.display_message("Returning to method editor.\n");
    return;
  }

  Interface.display_message("Type \"help\" to view all available editor commands.\n");
  do
  {
    Interface.display_message("-> ");

    input = Interface.get_user_input();
    
    if(input == "help")
      Interface.print_parameter_commands();
    
    else if(input == "view")
      Interface.display_class(currentClass);
    
    else if(input == "add")
      add_parameter(className, methodName);
    
    else if(input == "delete")
      delete_parameter(className, methodName);
    
    else if(input == "rename")
      rename_parameter(className, methodName);
    
    else if(input == "switch_method")
    {
      //recursive call
      edit_parameters(className);
      return;
    }
    else if(input == "exit")
    {
      Interface.display_message("You have exited the parameter editor.\n");
      Interface.display_message("Returning to method editor.\n");
      return;
    }
    else
      Interface.display_message("Invadid command! Type \"help\" to view all available parameter editor commands.\n");


    if(!Model.get_class_by_name(className, currentClass))
    {
      Interface.display_message("The changes were successfully made, but failed to update view.\n");
    }
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
  try
  {
      Model.load_model_from_json(fileName);
  }
  catch (UMLErrorCode e)
  {
      Interface.display_message("Loading from JSON failed: \n");
      Interface.display_message(UMLException::error_to_string(e) + "\n");
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




//ADDING
/*************************/


void UMLController::add_field(string className)
{
  string fieldName;
  Interface.display_message("Type a name for the field you\'d like to add. -> ");
  fieldName = Interface.get_user_input();

  //UMLAttribute newAttribute {attName};
  ClassField newField {fieldName};

  if(!Model.add_class_field(className, newField))
  {
    Interface.display_message("Error! Could not add new field.\n");
    return;
  }

  Interface.display_message("You have added the field \"" + fieldName + "\" to the class \"" + className + "\".\n");
}



/*************************/

void UMLController::add_method(string className)
{
  string methodName;
  Interface.display_message("Type a name for the method you\'d like to add. -> ");
  methodName = Interface.get_user_input();

  //UMLAttribute newAttribute {attName};
  ClassMethod newMethod {methodName};

  if(!Model.add_class_method(className, newMethod))
  {
    Interface.display_message("Error! Could not add new method.\n");
    return;
  }

  Interface.display_message("You have added the method \"" + methodName + "\" to the class \"" + className + "\".\n");
  Interface.display_message("How many parameters would you like to give this method? -> ");
  unsigned int parameterCount = Interface.user_int_input();
  
  for(int i = 0; i < parameterCount; i++)
  {
    if(!add_parameter(className, methodName))
      i--;
  }

  Interface.display_message("Complete!\n");
}

/*************************/

bool UMLController::add_parameter(string className, string methodName)
{

  Interface.display_message("Type a name for your parameter -> ");
  string parameterName = Interface.get_user_input();

  MethodParameter newParameter {parameterName};
        
  if(!Model.add_class_method_parameter(className, methodName, newParameter))
  {
    Interface.display_message("Error! The parameter \"" + parameterName + "\" could not be created.\n");
    Interface.display_message("Either the parameter already exists, or the name is invalid.\n");
    return false;
  }
    Interface.display_message("The parameter \"" + parameterName + "\" was successfully created!\n");
    return true;
}






//DELETING
/*************************/

void UMLController::delete_field(string className)
{
  string fieldName;
  Interface.display_message("Type the name of the field you\'d like to delete. -> ");
  fieldName = Interface.get_user_input();

  if(!Model.remove_class_field(className, fieldName))
  {
    Interface.display_message("Error! Could not delete field.\n");
    return;
  }
  Interface.display_message("The field \"" + fieldName + "\" was deleted.\n");
}

/*************************/

void UMLController::delete_method(string className)
{
  string methodName;
  Interface.display_message("Type the name of the method you\'d like to delete. -> ");
  methodName = Interface.get_user_input();

  if(!Model.remove_class_method(className, methodName))
  {
    Interface.display_message("Error! Could not delete method.\n");
    return;
  }
  Interface.display_message("The method \"" + methodName + "\" was deleted.\n");
}

/*************************/

void UMLController::delete_parameter(string className, string methodName)
{
  string parameterName;
  Interface.display_message("Type the name of the parameter you\'d like to delete. -> ");
  parameterName = Interface.get_user_input();

  if(!Model.does_class_method_have_parameter(className, methodName, parameterName))
  {
    Interface.display_message("Error! The parameter you typed does not exist.\n");
    return;
  }

  if(!Model.remove_class_method_parameter(className, methodName, parameterName))
  {
    Interface.display_message("Error! Could not delete parameter.\n");
    return;
  }
  Interface.display_message("The parameter \"" + parameterName + "\" was deleted.\n");
}




//RENAMING
/*************************/

/**
 * @brief I deleted rename_attribute() instead of commenting it out, because
 * there was no function in the model to rename attributes, so I had to do
 * it manually in the controller back then. But now it's super easy! :D
 * It's basically exactly like what I have in rename_method().
 * 
 */
void UMLController::rename_field(string className)
{
  string fieldNameFrom;
  string fieldNameTo;

  Interface.display_message("Type the name of the field you\'d like to rename FROM -> ");
  fieldNameFrom = Interface.get_user_input();

  if(!Model.does_class_have_field(className, fieldNameFrom))
  {
    Interface.display_message("Error! The field you typed does not exist.\n");
    return;
  }

  Interface.display_message("Type the name of the field you\'d like to rename TO -> ");
  fieldNameTo = Interface.get_user_input();

  if (Model.does_class_have_field(className, fieldNameTo))
  {
    Interface.display_message("Error! That name is already taken.\n");
    return;
  }

  Model.rename_class_field(className, fieldNameFrom, fieldNameTo);
  Interface.display_message("Field successfully renamed!\n");
}

/*************************/

void UMLController::rename_method(string className)
{
  string methodNameFrom;
  string methodNameTo;

  Interface.display_message("Type the name of the method you\'d like to rename FROM -> ");
  methodNameFrom = Interface.get_user_input();

  if(!Model.does_class_have_method(className, methodNameFrom))
  {
    Interface.display_message("Error! The method you typed does not exist.\n");
    return;
  }

  Interface.display_message("Type the name of the method you\'d like to rename TO -> ");
  methodNameTo = Interface.get_user_input();

  if (Model.does_class_have_method(className, methodNameTo))
  {
    Interface.display_message("Error! That name is already taken.\n");
    return;
  }

  Model.rename_class_method(className, methodNameFrom, methodNameTo);
  Interface.display_message("Method successfully renamed!\n");
}

/*************************/

void UMLController::rename_parameter(string className, string methodName)
{
  string paramNameFrom;
  string paramNameTo;

  Interface.display_message("Type the name of the parameter you\'d like to rename FROM -> ");
  paramNameFrom = Interface.get_user_input();

  if(!Model.does_class_method_have_parameter(className, methodName, paramNameFrom))
  {
    Interface.display_message("Error! The parameter you typed does not exist.\n");
    return;
  }

  Interface.display_message("Type the name of the parameter you\'d like to rename TO -> ");
  paramNameTo = Interface.get_user_input();
  
  if(Model.does_class_method_have_parameter(className, methodName, paramNameTo))
  {
    Interface.display_message("Error! That name is already taken.\n");
    return;
  }

  Model.rename_class_method_parameter(className, methodName, paramNameFrom, paramNameTo);
  Interface.display_message("Parameter sucessfully renamed!\n");
}