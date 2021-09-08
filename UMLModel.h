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

        // Internal method for getting an iterator to the class in the model by name.
        std::list<UMLClass>::iterator get_class_iter_by_name(std::string className);
        
    public:
        // Checks to see if the class name already exists in the model.
        // Returns true if the class exists in the model already, and false otherwise.
        bool does_model_contain_class(std::string className);

        // Adds a class to the model from a name alone.
        // Returns true if the add was successful, false if it failed.
        bool add_class(std::string className);

        // Adds a class to the model from a name and a vector of attributes.
        // Returns true if the add was successful, false if it failed.
        bool add_class(std::string className, std::vector<UMLAttribute> attributes);

        // Removes a class from the model by name.
        // Returns true if the removal was successful, false otherwise.
        bool remove_class(std::string className);

        // Gets a reference to the UMLClass object in the model by the name.
        // This should mainly be used for editing the class's attributes directly.
        UMLClass& get_class_by_name(std::string className);

        // Returns a list that contains all the current classes in the model.
        std::list <std::string> get_all_class_names();

};

#endif