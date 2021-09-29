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

void ConsoleView::display_class(string name)
{
  cout << "--> " << name << "\n";
}

/*************************/

void ConsoleView::display_attribute(string name)
{
  cout << "    : " << name << "\n";
}

/*************************/

void ConsoleView::display_relationship(string source, string destination)
{
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