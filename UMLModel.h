#ifndef UML_MODEL
#define UML_MODEL

#include <list>
#include "UMLAttribute.h"
#include "UMLClass.h"
#include "UMLRelationship.h"

/*
    The UMLModel will hold all the data for the current running program. It will hold
    all the class, relationship, and attribute data. Other classes can access the data
    indirectly via method calls. 

    Save/Loading from Json may want to be relegated to another class instead of here
    as good practice for separation of concerns. 
*/
class UMLModel {
    private:

        // Holds all the existing classes in the current model. 
        // Duplicates should not be allowed in this list.
        // Any insert/deletions to this list should go through the add/remove methods.
        std::list <UMLClass> AllClasses;

        //Contains all current existing relationships
        //Relationship must have name, source, destination
        //No duplicate names allowed
        std::list <UMLRelationship> AllRelationships;

        // Internal method for getting an iterator to the class in the model by name.
        std::list<UMLClass>::iterator get_class_iter_by_name(std::string className);

        std::list<UMLRelationship>::iterator get_relationship_iter_by_name(std::string relationshipName);

        friend class JSONFileSys;
        
    public:

        UMLModel();
        ~UMLModel();
        
        // Checks to see if the class name already exists in the model.
        // Returns true if the class exists in the model already, and false otherwise.
        bool does_class_exist(std::string className);

        // Adds a class to the model from a name alone.
        // Returns true if the add was successful, false if it failed.
        bool add_class(std::string className);

        // Adds a class to the model from a name and a vector of attributes.
        // Returns true if the add was successful, false if it failed.
        bool add_class(std::string className, std::vector<UMLAttribute> attributes);

        // Removes a class from the model by name.
        // Returns true if the removal was successful, false otherwise.
        bool remove_class(std::string className);

        // Modify a class name from the nameFrom parameter to the nameTo parameter.
        // Returns false in cases where either the nameFrom doesnt exist or the
        // nameTo is not a valid name. Returns true if the modify was successful.
        bool modify_class_name(std::string nameFrom, std::string nameTo);

        // Returns a string list that contains all the current classes in the model.
        const std::list <std::string> get_all_class_names();

        bool does_relationship_exist(std::string relationshipName);

        bool add_relationship(std::string relationshipName, UMLClass src, UMLClass dest);

        bool remove_relationship(std::string relationshipName);

        const std::list <UMLRelationship> get_class_relationships(std::string className);
        
        // Returns relationship object by name
        // Will return an empty relationship object if it doesnt exist, which
        // may result in undesired behavior! Call does_relationship_exist first! :)
        const UMLRelationship get_relationship_by_name(std::string relationshipName);

};

#endif