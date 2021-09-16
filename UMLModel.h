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

        bool add_class(UMLClass newClass);

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

        bool add_class_attribute(std::string className, UMLAttribute attribute);

        bool remove_class_attribute(std::string className, std::string attributeName);

        // Returns a string list that contains all the current classes in the model.
        const std::list <std::string> get_all_class_names();

        //Checks if relationship with name already exists
        bool does_relationship_exist(std::string relationshipName);

        //Does not allow duplicate relationship names
        //If name valid, checks that both source and destination class exist
        //If so, relationship added to list AllRelationships
        bool add_relationship(std::string relationshipName, UMLClass src, UMLClass dest);

        //Removes relationship from list AllRelationships
        bool remove_relationship(std::string relationshipName);

        //Checks that class exists
        //Returns list of relationships where className is either its source or destination
        const std::list <UMLRelationship> get_class_relationships(std::string className);

        //Returns list of all current existing and valid relationships.
        const std::list <UMLRelationship> get_all_relationships();

        //Called when a class is deleted
        //Checks if class being deleted is either a source or destination of a relationship
        //If so, relationship is also deleted because relationshp cannot exist without source AND destination.
        void ensure_relationship_delete(std::string className);
        
        // Gets a copy of the relationship specified by name and puts it into the outRelationship variable
        // Returns true if the relationship exists, false otherwise
        // NOTE: modifying the contents of outRelationship does not modify the contents of the model.
        bool get_relationship_by_name(std::string relationshipName, UMLRelationship& outRelationship);

        // Gets a copy of the class specified by name and puts it into the outClass variable
        // Returns true if the class exists, false otherwise
        // NOTE: modifying the contents of outClass does not modify the contents of the model.
        bool get_class_by_name(std::string className, UMLClass& outClass);

        // Saves the current model to a json file, "fileName.json"
        // 
        // NOTE: currently does not throw exceptions, but in the future it may need to.
        void save_model_to_json(std::string fileName);

        // Loads the current model from a json file, "fileName.json"
        // Returns false either if the filename doesnt exist or the model trying to be 
        // loaded is not valid
        //
        // NOTE: In the future this may simply throw custom exceptions.
        bool load_model_from_json(std::string fileName);
};

#endif