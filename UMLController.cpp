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

UMLController::UMLController(UMLModel newModel)
  : Model(newModel)
{}

/***********************************************************/
//Functions

int main()
{
  cout << "Type \"help\" for the list of commands.\n";
  cout << "Type \"exit\" to quit your current session.\n";
  
  execute();

  return 0;
}


/*************************/

/**
 * @brief Takes in user input and does string comparisons to see if the user typed
 * in a valid command, and does different things based on which command was typed.
 * 
 * 
 */
void UMLController::execute()
{
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
      listRelationships();
    
    else if(userInput == "create_class")
      createClass();
    
    else if(userInput == "create_relationship")
      createRelationship();

    else if(userInput == "delete_class")
      deleteClass();
      
    else if(userInput == "delete_relationship")
      deleteRelationship();

    else if (userInput == "exit")
      cout << "\n";
    else
    {
      cout << "Invadid command! Type \"help\" to view all available commands.\n";
    }

  } while (userInput != "exit");
  
  //This is when the user quits their current session. But I figured I'd make it a little more interesting...  >:D
  cout << "YOU DIED\n";
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
    << "list_relaionships   : Lists all relationships created by the user. (e.g. [source -> destination])\n"
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
  std::list<string> ClassList = Model.get_all_class_names();


  //if no classes, error message.
  if (ClassList.size() == 0)
    cout << "You have no classes.\n";
  
  //else iterate through the collection of classes and list them all.
  else
  {
    //The compiler was angry at me for making a for each loop, so I turned it back into a standard for loop.
    for(long unsigned i = 0; i < ClassList.size(); i++)
    {
      cout << Classes[i];
      
      //'if statement' fixes fencepost issue
      if (i < Classes.size() - 1)
        cout << ", ";
    }
  }

  cout << "\n";
}

/*************************/

/**
 * @brief Lists all relationships the user has created.
 * 
 */
void listRelationships()
{
  if (Relships.size() == 0)
    cout << "You have no relationships.\n";

  else
  {
    cout <<   "SOURCE : DESTINATION\n";

    for(string& i: Relships)
    {
      cout << i << "\n";
    }
  }
  
}

/*************************/

/**
 * @brief The user is prompted to name the class (15 characters max)
 * and then it pushes the class into the vector.
 * 
 */
void createClass()
{
  bool tryAgain;
  string user_input; 
  cout << "Choose a name for your class. (15 characters max)\n\nclass> ";
  cin >> user_input;

  //if user input exceeds 15 characters
  if (user_input.length() > 15)
  {
    cout << "\nWhat part of \"15 characters max\" don\'t you understand???\n";
    tryAgain = continuePrompt("class> ");
    
    if(tryAgain)
      createClass();
    
    return; 
  }
  //if the class name is <= 15 characters
  else
  {
    bool letterFirst = false;
    bool alphaNumeric = false;

    vector<char> alphabetCheck = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    vector<char> numCheck = {'0','1','2','3','4','5','6','7','8','9'};

    //First, checks to see if first character of class name is a letter
    for (long unsigned int i = 0; i < alphabetCheck.size(); i++)
    {
      if (user_input[0] == alphabetCheck[i])
      {
        letterFirst = true;
        break;
      }
    }
    
    //Iterates through each character of the parsed input and checks if it's a letter or number.
    for(long unsigned int i = 1; i < user_input.size(); i++)
    {
      alphaNumeric = false;

      //checks for letters
      for(long unsigned int j = 0; j < alphabetCheck.size(); j++)
      {
        if (user_input[i] == alphabetCheck[j])
        {
          alphaNumeric = true;
          break;
        }
      }
      
      if(!alphaNumeric)
      {
        //checks for numbers
        for (long unsigned int j = 0; j < numCheck.size(); j++)
        {
          if (user_input[i] == numCheck[j])
          {
            alphaNumeric = true;
            break;
          }
        }
      }
    }
   
    if (letterFirst && alphaNumeric)
    {
      //Checks for duplicate classes
      bool dupCheck = searchVector(user_input, Classes);
      if (!dupCheck)
      {
        Classes.push_back(user_input);
        cout << "You created a new class called \"" << user_input << "\"\n";
      }
      else
      {
        cout << user_input << " already exists. Try something new.\n";
        tryAgain = continuePrompt("class> ");
        
        if(tryAgain)
          createClass(); 
      }
      
    } 
    else
    {
      cout << "Invalid class name. Your classes must start with a letter, and all characters must be alpha-numeric.\n";
      tryAgain = continuePrompt("class> ");
    
      if(tryAgain)
        createClass(); 
    }
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
void createRelationship()
{
  string source;
  string destination;
  string cmdLine = "relship> ";
  


  cout << "Type in a class name you'd like to use for the source.\n" << cmdLine;
  cin >> source;

  
  if (!searchVector(source,Classes))
  {
    cout << "Error! The class you typed does not exist.\n";
    if(continuePrompt(cmdLine))
    {
      createRelationship();
      return;
    }
  }
  
  bool failCase = false;
  do
  {
    if (failCase)
    {
      cout << "Error! The class you typed does not exist!\n";
      if(!continuePrompt(cmdLine))
        return;
    }
    else if (source == destination)
    {
      cout << "Error! You can't have a relationship between a class and itself!\n";
      if (!continuePrompt(cmdLine))
        return;
    }
    
    cout << "Type in a class name you'd like to use for the destination.\n" << cmdLine;
    cin >> destination;
    failCase = true;
  } while (!searchVector(destination, Classes) && source != destination);

  
  string newRelship = "[" + source + " -> " + destination + "]";
  
  if(searchVector(newRelship, Relships))
  {
    cout << "This relationship already exists.\n";
    if (continuePrompt(cmdLine))
      createRelationship();
  }
  else
  {
    Relships.push_back(newRelship);
    cout << "You created a new relationship:\n"
    << newRelship << "\n";
  }
}

/*************************/

/**
 * @brief 
 * 
 */
void deleteRelationship()
{
  string source;
  string destination;
  string cmdLine = "-relship> ";
  cout << "Enter the source of the relationship you\'d like to delete.\n" << cmdLine;
  cin >> source;

  if (!search_in_relship(source, 1))
  {
    cout << "This class is not a source.\n";
    if(continuePrompt(cmdLine))
    {
      deleteRelationship();
      return;
    }
  }
  else
  {
    bool failCase = false;
    do{
      
      if (failCase)
      {
        cout << "This class is not a destination.\n";
        if(!continuePrompt(cmdLine))
          return;
      }

      cout << "Enter the destination of the relationship you\'d like to delete.\n" << cmdLine;
      cin >> destination;
      failCase = true;

    }while(!search_in_relship(destination, 2));
    
    string testRelship = "[" + source + " -> " + destination + "]";
    
    long unsigned int index = searchVectorIndex(testRelship, Relships);
    if ((int) index == -1)
    {
      cout << "Error! The relationship " << testRelship <<  " was not found.\n";
      if(continuePrompt(cmdLine))
      {
        deleteRelationship();
        return;
      }
    }
    else
    {
      Relships.erase(Relships.begin() + index);
      cout << "The relationship " << testRelship << " has been deleted.\n";
    }

  }

}

/*************************/

/**
 * @brief 
 * 
 */
void deleteClass()
{
  string input;
  string cmdLine = "-class> ";
  cout << "Type the name of the class you'd like to delete.\n" << cmdLine;
  cin >> input;

  if (!searchVector(input, Classes))
  {
    cout << "Error! The class you typed does not exist!\n";
    if (continuePrompt(cmdLine))
      deleteClass();
      
    return;
  }
  vector<long unsigned int> TargetIndexes;
  if (Relships.size() != 0)
  {
    for(long unsigned int i; i < Relships.size(); i++)
    {
      string source = sourceParse(Relships[i]);
      if (input == source)
      {
        TargetIndexes.push_back(i);
      }
      //It's +5 because that's the amount of iterations needed to surpass
      //the spaces and the arrow.
      else if (input == destParse(Relships[i], source.size() + 5))
      {
        TargetIndexes.push_back(i);
      }
    }

    if(TargetIndexes.size() != 0)
    {
      cout << "WARNING! This class is a member of the following relationships:\n";
      for (long unsigned int i; i < TargetIndexes.size(); i++)
      {
        cout << Relships[TargetIndexes[i]] << "\n";
      }
      cout << "Deleting this class will also delete these relationships.\n"
      << "Do you wish to proceed?\n";
      do
      {
        cout << "Type \"y\" to proceed or \"n\" to cancel.\n" << cmdLine;
        cin >> input;
      } while (input != "y" || input != "n");
      
      for (long unsigned int i; i < TargetIndexes.size(); i++)
      {
        Relships.erase(Relships.begin() + TargetIndexes[i]);
      }
      cout << "The relationship(s) have been deleted.\n";
      
    }
  }
  long unsigned int index = searchVectorIndex(input, Classes);
  
  Classes.erase(Classes.begin() + index);
  cout << "The class \"" << input << "\" has been deleted.\n";
}





/***********************************************************/
//Helper Functions

/**
 * @brief Depending on the user's stubbornness and/or stupidity, the user will be prompted over and over
 * again until he/she FINALLY types "y" or "n".
 * 
 * @param commandLine 
 * @return true 
 * @return false 
 */
bool continuePrompt(string commandLine)
{
  string user_input;

  cout << "Type \"y\" to try again, or \"n\" to quit.\n\n" << commandLine;
  cin >> user_input;
  
  while (1) 
  {
      
    if (user_input == "y"){
      return true;
    }
    else if (user_input == "n"){
      return false;
    }
    else{ // if the user doesn't type "y" or "n"

      
      cout << "Bruh! Your instructions could not possibly be any more clear!\n" 
      << "Type \"y\" to try again, or \"n\" to quit!\n\n" 
      << commandLine;
      cin >> user_input;
    }
  }
}




/**
 * @brief Searches the vector of classes to see if any of the classes match the user input.
 * If found, returns the index number. If not found, returns -1.
 * 
 * @param input 
 * @return long unsigned int 
 */
long unsigned int searchVectorIndex(string input, vector<string> collection)
{
  for(long unsigned int i = 0; i < collection.size(); i++)
  {
    if (collection[i] == input)
      return i;      
  }
  return -1;
}




/**
 * @brief Searches the vector of classes to see if any of the classes match the user input.
 * if found, returns true. If not found, returns false.
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool searchVector(string input, vector<string> collection)
{
  long unsigned int index = searchVectorIndex(input, collection);
  return (int)index != -1;
}



/**
 * @brief Looks through a given relationship and returns the source.
 * 
 * @param relship 
 * @return string 
 */
string sourceParse(string relship)
{
  string source = "";
  //i = 1 because we don't want '['
  for(long unsigned int i = 1; relship[i] != ' '; i++) {
    source += relship[i];
  }
  return source;
}




/**
 * @brief Looks through a given relationship and returns the destination.
 * 
 * This function is called by another function that searches for the 
 * source and the destination. So for efficiency's sake, the index is
 * passed as a parameter. 
 * 
 * @param relship
 * @param index
 * @return source
 */
string destParse(string relship, long unsigned int index)
{
  string destination = "";
  if (index == 0)
  {
    while(relship[index] != '>' && index < relship.size())
    {
      index++;
    }
    index += 2;
  }
  
  while(index < relship.size() && relship[index] != ']')
  {
    destination += relship[index];
    index++;
  }
  return destination;
}




/**
 * @brief Looks through the entire Relships vector to see if
 * the specified class is in there.
 * 
 * Option 1 searches the source.
 * Option 2 searches the destination.
 * 
 * Returns true if found, returns false if not found.
 * 
 * @param Class 
 * @param option 
 * @return true 
 * @return false 
 */
bool search_in_relship(string Class, int option)
{

  string subject;

  if(option == 2)
  {
    for(string& i: Relships)
    {
      subject = destParse(i, 0);
      if (subject == Class)
        return true;
    }
  }
  else
  {
    for(string& i: Relships)
    {
      subject = sourceParse(i);
      
      // Only return if true.
      if(subject == Class)
        return true;
    }
  }
  return false;
}