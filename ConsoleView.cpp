
PrintClassName(UMLClass X){
    
    std::cout<< x.get_class_name(); 
    
   }

PrintClassAttribute(UMLClass x){
    
    for(const UMLClass & e : Classes)
    {
        std::cout << "UMLClass:" << std::endl;
        std::cout << e.get_all_attributes() << std::endl;
    }
    
}


PrintClassRelations(UMLRelationship x){
    
    std::cout<< x.get_relationship_name();
}

PrintSourceandDest(UMLRelationship x){
    std::cout << x. get_src_class() << x.get_dest_class();
}
