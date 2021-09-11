
PrintClassName(UMLClass X){
    
    std::cout<< x.get_class_name(); 
    
   }

PrintClassAttribute(UMLClass x){
    
    std::cout << "List of Classes:";
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
    
}


PrintClassRelations(UMLRelationship x){
    
    std::cout<< x.get_relationship_name();
}

PrintSourceandDest(UMLRelationship x){
    std::cout << x. get_src_class() << x.get_dest_class();
}
