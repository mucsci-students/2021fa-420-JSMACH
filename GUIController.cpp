#include "GUIController.h"
#include "UMLModel.h"
#include "GUIView.h"
#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

GUIController::GUIController(UMLModel& model, GUIView& view)
	: Model(&model), View(&view)
{
    // Link view buttons to function calls within controller
    View->Button.events().click([&] {
        std::string userText = View->InputText.text();
        if(userText != "")
            parse_input(userText);
    });

    View->InputText.events().key_press([&](const arg_keyboard& arg) {
        if (arg.key == keyboard::enter)
            parse_input(View->InputText.text());
    });
}

GUIController::~GUIController() {}

void GUIController::execute()
{
    View->run();
}

void GUIController::parse_input(std::string userInput)
{
    if (userInput == "help")
    {
        View->display_msg(HELP_TEXT);
    }
    else
    {
        View->display_msg("Unknown command. Type help for commands");
    }
    View->clear_input_text();
}