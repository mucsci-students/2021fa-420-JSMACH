#include "GUIView.h"

#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

using namespace nana;

GUIView::GUIView()
{
    // Constructs all properties of GUI
    Form.size(size(550, 720));
    Form.caption("JSMACH UML Editor");
    CentralWidgets.bind(Form);

    DisplayText.create(Form);
    DisplayText.text_align(align::left);
    DisplayText.caption("Type 'help' for a list of commands\nType 'quit' to quit\n");

    // Buttons need to be INITIALIZED HERE
    // They need to be linked in the controller
    Button.create(Form);
    Button.caption("Go");

    InputText.create(Form);
    InputText.editable(true);
    InputText.multi_lines(false);

    CentralWidgets.div("<vert <display weight=80%> <input weight=10%> <go weight=10%>>");
    CentralWidgets["display"] << DisplayText;
    CentralWidgets["input"] << InputText;
    CentralWidgets["go"] << Button;
    CentralWidgets.collocate();
}

GUIView::~GUIView() {}

void GUIView::display_msg(std::string msg)
{
    DisplayText.caption(msg);
}

void GUIView::clear_input_text()
{
    InputText.reset();
}

void GUIView::run()
{
    // Shows form and run
    Form.show();
    nana::exec();
}