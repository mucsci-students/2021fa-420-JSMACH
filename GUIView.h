#ifndef UML_GUI_VIEW
#define UML_GUI_VIEW

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include <nana/gui/widgets/combox.hpp>

#include <string>
#include <list>
#include <vector>
#include "UMLClass.h"
#include "UMLModel.h"
#include "UMLRelationship.h"
#include "ClassField.h"
#include "ClassMethod.h"
#include "MethodParameter.h"

using namespace nana;

class GUIView {
	private:
		UMLModel* Model;

	public:
		form Form;
		place CentralWidgets;
		button Button;
		label DisplayText;
		textbox InputText;

		form JSONForm;
		place JSONWidgets;
		button JSONButton;
		textbox JSONInput;

		form ClassWindow;
		place ClassWidgets;
		button ClassSubmit;
		textbox ClassNameText;
		label ClassNameTextLabel;
		textbox ClassFields;
		label ClassFieldsLabel;
		textbox ClassMethods;
		label ClassMethodsLabel;

		form RelationshipWindow;
		place RelationshipWidgets;
		button RelationshipSubmit;
		label SrcLabel;
		textbox RelationshipSrc;
		label DestLabel;
		textbox RelationshipDest;
		combox RelationshipTypeSelect;

		form DeleteClassWindow;
		place DeleteClassWidgets;
		button DeleteClassButton;
		textbox DeleteClassInput;

		form DeleteRelWindow;
		place DeleteRelWidgets;
		button DeleteRelButton;
		textbox DeleteRelSrcInput;
		textbox DeleteRelDestInput;
		label DeleteRelSrcLabel;
		label DeleteRelDestLabel;

		form EditClassWindow;
		place EditClassWidgets;
		button EditClassSubmit;
		textbox EditClassNameText;
		label EditClassNameTextLabel;
		textbox EditClassFields;
		label EditClassFieldsLabel;
		textbox EditClassMethods;
		label EditClassMethodsLabel;

		form GetClassWindow;
		place GetClassWidgets;
		button GetClassButton;
		textbox GetClassInput;

		GUIView(UMLModel& model);
		~GUIView();

		void run();
		void stop();

		void display_msg(std::string msg);

		void clear_input_text();

		void display_classes();

		std::string single_class_as_string(UMLClass& currentClass);
		std::string single_relationship_as_string(UMLRelationship& currentRelationship);

		void display_relationships();

		void build_json_window();
		void display_json_window();
		void close_json_window();

		void build_class_builder_window();
		void display_class_builder_window();
		void close_class_builder_window();

		void build_relationship_window();
		void display_relationship_window();
		void close_relationship_window();

		void build_delete_class_window();
		void display_delete_class_window();
		void close_delete_class_window();

		void build_delete_relationship_window();
		void display_delete_relationship_window();
		void close_delete_relationship_window();

		void build_edit_class_window();
		void display_edit_class_window(UMLClass& current);
		void close_edit_class_window();

		void build_get_class_window();
		void display_get_class_window();
		void close_get_class_window();
};



#endif