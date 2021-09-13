#include "ConsoleView.h"

//All these functions return void, they are simply here 
//for the user to call when they want to get information on 
//a CLASS (or a list of all classes), RELATIONSHIP, or ATTRIBUTE

//Prtint class will be used to print the name of a class given a UMLClass object
//By using the get_class_name function from the UMLClass, it then prints the name of the Class given
//@Para: UMLClass OBJ
void ConsoleView::PrintClassName(UMLClass X){
    
    std::cout<< x.get_class_name(); 
    
 }

//PrintClassAttribute is used to print the names of the Attributes in a given UMLClass Object 
// The attirbutes are stored in a vector so to print out each of the attributes in a class
// we must iterate over the vector of elements while we print each attirbute stored 
//the std::for_each takes in two iterators and a function which will be applied 
//@Para: UMLClass OBJ
void ConsoleView::PrintClassAttribute(UMLClass x){
    auto y= x.get_all_attributes(); //vector created 
    std::cout << "List of Classes:";
    print= std::ostream_iterator<int>(std::cout);//print out each item
    std::for_each(y.cbegin(), y.cend(), print); //iteration 
    std::cout << '\n';
    
}

//PrintClassRelations Will print the name of a given relationship 
//By using the get_relationship_name we can get the class name
//@Para: UMLRelationship OBJ
void ConsoleView::PrintClassRelations(UMLRelationship x){
    
    std::cout<< x.get_relationship_name();
}


//Print both the source and destination
//Using both the get_src_class and get_dest_class 
//@Para: UMLRelationship OBJ
void ConsoleView::PrintSourceandDest(UMLRelationship x){
    //std::cout << x.get_src_class().get_class_name() << x.get_dest_class().get_class_name();
    std::cout << x.get_src_class()<< x.get_dest_class();
}
