#ifndef UML_GUI_VIEW
#define UML_GUI_VIEW

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>

#include <string>
#include <list>
#include "UMLClass.h"
#include "UMLRelationship.h"

using namespace nana;

class GUIView {
	private:

	public:
		form Form;

		place CentralWidgets;
		button Button;
		label DisplayText;
		textbox InputText;

		GUIView();
		~GUIView();

		void run();

		void display_msg(std::string msg);

		void clear_input_text();


};



#endif