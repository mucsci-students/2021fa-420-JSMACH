#include "ConsoleView.h"
#include "UMLRelationship.h"
#include <iostream>
//All these functions return void, they are simply here 
//for the user to call when they want to get information on 
//a CLASS (or a list of all classes), RELATIONSHIP, or ATTRIBUTE



std::ostream& operator<<(std::ostream& out, const UMLRelationship& dt) {
    
    out << dt;
    
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<UMLAttribute>& vec) {
    
    out << vec;
    
    return out;
}
std::ostream& operator<<(std::ostream& out, const UMLClass& display) {
    
    out << display;
    
    return out;
}

std::ostream& operator<<(std::ostream& out, const UMLAttribute& dt)
{
    out << dt;
    return out;
}




//Prtint class will be used to print the name of a class given a UMLClass object
//By using the get_class_name function from the UMLClass, it then prints the name of the Class given
//@Para: UMLClass OBJ
void ConsoleView::print_class_name(UMLClass display){
    
    std::cout<< display.get_class_name()<< "/n"; 
    
 }



//PrintClassAttribute is used to print the names of the Attributes in a given UMLClass Object 
// The attirbutes are stored in a vector so to print out each of the attributes in a class
// we must iterate over the vector of elements while we print each attirbute stored 
//the std::for_each takes in two iterators and a function which will be applied 
//@Para: UMLClass OBJ
void ConsoleView::print_class_attribute(UMLClass display){
     auto y=display.get_all_attributes();;//vector created 
    for(auto i: y)
    std::cout << i<< "/n";
    
}

//PrintClassRelations Will print the name of a given relationship 
//By using the get_relationship_name we can get the class name
//@Para: UMLRelationship OBJ
void ConsoleView::print_class_relations(UMLRelationship display){
    
    std::cout<< display.get_relationship_name()<< "/n";
}


//Print both the source and destination
//Using both the get_src_class and get_dest_class 
//@Para: UMLRelationship OBJ
void ConsoleView::print_source_and_dest(UMLRelationship display){
    std::cout << display.get_src_class().get_class_name()  << display.get_dest_class().get_class_name()<< "/n";
    
}

// Print the list of classes stored in the current model
//Retun the list of classes stored and iterate over each
//element while we print it out 
void ConsoleView::print_all_classes(std::list<std::string> display){
    
    for (auto y : display) 
    std::cout <<y<< "/n";
}
