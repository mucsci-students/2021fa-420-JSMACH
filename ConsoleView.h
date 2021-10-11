#ifndef UML_CONSOLE_VIEW
#define UML_CONSOLE_VIEW

#include "UMLClass.h"
#include "UMLRelationship.h"


#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using std::string;

/*
    The ConsoleView is responsible for displaying information to the user.
    Very little if any application logic is handled in the view class.
*/
class ConsoleView
{

public:
  ConsoleView();
  

  // Prints a command line symbol and takes in user input.
  string console_menu();

  // Takes in user input. This method is redundant in ConsoleView.cpp,
  // but it's a necessary evil for the IView to work properly.
  string attribute_menu();
  
  // Returns a string typed by the user.
  string get_user_input();

  // Takes in a string as a parameter and prints it out.
  void display_message(string msg);

  // Takes in the class name and prints it in a specific format.
  void display_class(UMLClass currentClass);

  // Prints out the method with its parameters in a specific format.
  void display_method(ClassMethod currentMethod);

  // Takes in the source name and the destination name, then
  // it labels and prints them in a specific format.
  void display_relationship(string source, string destination, string rType);

  // Takes in user input. This method is redundant in ConsoleView.cpp,
  // but it's a necessary evil for the IView to work properly.
  string get_relationship_type();

  // Prints a list of all available commands for the user to
  // type in the command line.
  void help();

  // Returns an unsinged int typed by the user. If the user types
  // something else, they will be prompted until they type a
  // valid unsigned int.
  unsigned int user_int_input();

  // Prints a list of all available commands the user can type
  // in the field editor menu.
  void print_field_commands();

  // Prints a list of all available commands the user can type
  // in the method editor menu.
  void print_method_commands();

  // Prints a list of all available commands the user can type
  // in the parameter editor menu.
  void print_parameter_commands();
  
};


#endif
