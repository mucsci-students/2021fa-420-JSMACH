/**
 * @file ConsoleView.cpp
 * @author Matt Giacoponello
 * @brief 
 * @version 0.1
 * @date 2021-09-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */


/***********************************************************/
//Include statements

#include "ConsoleView.h"
#include <iostream>
#include <vector>
#include <string.h>

/***********************************************************/
//Using declarations

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::list;

/***********************************************************/
//Constructor

ConsoleView::ConsoleView()
{}


/***********************************************************/
//Functions



string ConsoleView::console_menu()
{
  cout << "> ";
  string userInput = get_user_input();
  return userInput;
}

/*************************/

void ConsoleView::display_message(string msg)
{
  cout << msg;
}

/*************************/

string ConsoleView::get_user_input()
{
  string input;
  cin >> input;
  return input;
}

/*************************/

void ConsoleView::display_class(UMLClass currentClass)
{
  string className = currentClass.get_class_name();
  vector<ClassField> fields = currentClass.get_all_fields();
  vector<ClassMethod> methods = currentClass.get_all_methods();

  cout << "CLASS: " << className << "{\n";
  cout << "  Fields: [feature disabled]\n";
  
  for(unsigned int i = 0; i < fields.size(); i++)
  {
    cout << "    " << fields[i].get_field_name() << "\n";
  }
  
  cout << "  Methods:\n";
  for(unsigned int i = 0; i < methods.size(); i++)
  {
    cout << "    ";
    display_method(methods[i]);
  }
  cout << "}\n";
}

/*************************/
void ConsoleView::display_method(ClassMethod currentMethod)
{
  cout << currentMethod.get_method_name() << "(";

    list<MethodParameter> parameters = currentMethod.get_parameters();
    for (auto iter = parameters.begin(); iter != parameters.end(); iter++)
    {
      if(iter != parameters.begin())
        cout << ", ";
      
      cout << (*iter).get_name();
    }
    cout << ")\n";

}
/*************************/

void ConsoleView::display_relationship(string source, string destination, string rType)
{
  cout << "TYPE: \n\t" << rType << "\n";
  cout << "SOURCE: \n\t" << source << "\n";
  cout << "DESTINATION: \n\t" << destination << "\n";
}

/*************************/

/**
 * @brief ConsoleView.cpp and the GUI file have to have the same number of methods with the same
 * names in order for the IView to work properly. In the GUI version, this method will have a clickable box
 * for each option.
 * 
 * We need this to be a separate method because there are some circumstances where the user will still need
 * type in the GUI (such as naming things) and other cases where they are given clickable boxes of predetermined
 * options. And this method serves as a way to distiguish between the 2.
 * 
 * Here, in ConsoleView.cpp, this method is completely redundant. But it's a necessary evil for the IView to work.
 * 
 * @return string 
 */
string ConsoleView::attribute_menu()
{
  return get_user_input();
}

/*************************/

string ConsoleView::get_relationship_type()
{
  return get_user_input();
}

/*************************/

void ConsoleView::help()
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
  << "edit_fields         : User will be sent to a sub-menu, where they can enter in field editor\n"
  << "                      commands.\n\n"
  << "edit_methods        : User will be sent to a sub-menu, where they can enter in method editor\n"
  << "                      commands (including a parameter editor sub-sub-menu).\n\n" 
  << "load                : User will be prompted to type the name of the json file, and then it loads\n"
  << "                      the model from that file. WARNING! Existing progress will be overwritten!\n\n" 
  << "save                : User will be prompted to name the JSON file, which will contain their\n"
  << "                      current progress.\n\n" 
  << "quit                : Exit your current session.\n\n";

}

/*************************/

unsigned int ConsoleView::user_int_input()
{
  unsigned int num;

  while(!(cin >> num))
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input. Try again (input a number): ";
  }
  return num;
}

/*************************/

void ConsoleView::print_field_commands()
{
  cout << "FIELD EDITOR COMMANDS:\n"
    << "view         : View the current class with its fields.\n"
    << "add          : Add a new field.\n"
    << "delete       : Delete an existing field.\n"
    << "rename       : Rename an existing field.\n"
    << "switch_class : Allows the user to switch to a different class.\n"
    << "exit         : Quit the field editor and return to the normal interface.\n\n";

}

/*************************/

void ConsoleView::print_method_commands()
{
  cout << "METHOD EDITOR COMMANDS:\n"
    << "view            : View the current class with its methods.\n"
    << "add             : Add a new method.\n"
    << "delete          : Delete an existing method.\n"
    << "rename          : Rename an existing method.\n"
    << "switch_class    : Allows the user to switch to a different class.\n"
    << "edit_parameters : User will be sent to a sub menu to edit a method's parameters.\n"
    << "exit            : Quit the method editor and return to the normal interface.\n\n";
}

/*************************/

void ConsoleView::print_parameter_commands()
{
  cout << "PARAMETER EDITOR COMMANDS:\n"
    << "view          : View the current class with its fields, methods, and parameters.\n"
    << "add           : Add a new parameter.\n"
    << "delete        : Delete an existing parameter.\n"
    << "rename        : Rename an existing parameter.\n"
    << "switch_method : Allows the user to switch to a different method.\n"
    << "exit          : Quit the parameter editor and return to the method editor.\n\n";

}