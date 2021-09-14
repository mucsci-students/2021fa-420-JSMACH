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
std::ostream& operator<<(std::ostream& out, const UMLClass& x) {
    
    out << x;
    
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
void ConsoleView::Print_Class_Name(UMLClass X){
    
    std::cout<< X.get_class_name(); 
    
 }



//PrintClassAttribute is used to print the names of the Attributes in a given UMLClass Object 
// The attirbutes are stored in a vector so to print out each of the attributes in a class
// we must iterate over the vector of elements while we print each attirbute stored 
//the std::for_each takes in two iterators and a function which will be applied 
//@Para: UMLClass OBJ
void ConsoleView::Print_Class_Attribute(UMLClass x){
     auto y=x.get_all_attributes();;//vector created 
    for(auto i: y)
    std::cout << i;
    
}

//PrintClassRelations Will print the name of a given relationship 
//By using the get_relationship_name we can get the class name
//@Para: UMLRelationship OBJ
void ConsoleView::Print_Class_Relations(UMLRelationship x){
    
    std::cout<< x.get_relationship_name();
}


//Print both the source and destination
//Using both the get_src_class and get_dest_class 
//@Para: UMLRelationship OBJ
void ConsoleView::Print_Source_and_Dest(UMLRelationship x){
    std::cout << x.get_src_class().get_class_name()  << x.get_dest_class().get_class_name();
    
}
/* WAIT FOR MODEL.CPP
// Print the list of classes stored in the current model
//Retun the list of classes stored and iterate over each
//element while we print it out 
void ConsoleView::Print_All_Classes(UMLModel x){
    auto list=x.get_all_class_names();
    for (auto y : list) 
    std::cout <<y;
}
*/