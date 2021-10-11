#ifndef UML_GUI_CONTROLLER
#define UML_GUI_CONTROLLER

#include "UMLModel.h"
#include "GUIView.h"
#include <string>

enum JSONState { SAVE, LOAD };

class GUIController {
	private:
		UMLModel* Model;
		GUIView* View;

        JSONState State;

		const std::string HELP_TEXT = 
            "COMMANDS:\n\nlist_classes:\nLists all classes the user has created, as well as their attributes.\n\n"
            "list_relationships:\nLists all relationships created by the user. (e.g. [source -> destination])\n\n"
            "create_class:\n User will be prompted to name the class, and then it\'ll be created.\n\n"
            "create_relationship:\nUser will be prompted to type in a source class and a destination class.\n\n"
            "delete_class:\n User will be prompted to type the name of the class they\'d like to delete.\n\n"
            "delete_relationship:\nUser will be prompted to type the source and destination. The relationship will be no more, but the classes will still exist.\n\n"
            "edit_class:\nUser will be prompted to type the existing class name, and then will be prompted to modify any information they want about a class.\n\n"
            "load:\nUser will be prompted to type the name of the json file, and then it loads the model from that file. WARNING! Existing progress will be overwritten!\n\n"
            "save:\nUser will be prompted to name the JSON file, which will contain their current progress.\n\n"
            "quit:\nExit your current session.\n\n";

	public:
		GUIController(UMLModel& model, GUIView& view);
        ~GUIController();

		void execute();

		void parse_input(std::string userInput);

        void json_window();

        void add_class();
        bool build_class(std::string& className, std::string& fieldsBlob, std::string& methodsBlob);

        void add_relationship();
        bool build_relationship(std::string& classSrc, std::string& classDest, RelationshipType relationshipType);
		
        void remove_class();
        bool delete_class(std::string& className);

        void remove_relationship();
        bool delete_relationship(std::string& classSrc, std::string& classDest);

        void edit_class();
        void edit_class(std::string className);
        void edit_class(std::string& classNameBefore, std::string& enteredClassName, std::string& enteredFieldsBlob, std::string& enteredMethodsBlob);
};      


#endif