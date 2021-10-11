#include "GUIController.h"
#include "UMLModel.h"
#include "GUIView.h"
#include <iostream>
#include "UMLException.hpp"

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

std::vector<ClassField> parse_fields(std::string& fieldsBlob);
std::vector<ClassMethod> parse_methods(std::string& methodsBlob);

GUIController::GUIController(UMLModel& model, GUIView& view)
	: Model(&model), View(&view)
{
    // Link view buttons to function calls within controller
    View->Button.events().click([&] {
        std::string userText = View->InputText.text();
        if(userText != "")
            parse_input(userText);
    });

    // Link enter key press to parsing input
    View->InputText.events().key_press([&](const arg_keyboard& arg) {
        if (arg.key == keyboard::enter)
            parse_input(View->InputText.text());
    });

    // Link json button to save/load event
    View->JSONButton.events().click([&] {
        std::string userInput = View->JSONInput.text();
        std::string msg;
        if (State == JSONState::SAVE)
        {
            Model->save_model_to_json(userInput);
            msg = "Saved to " + userInput.append(".json");
        }
        else
        {
            try
            {
                Model->load_model_from_json(userInput);
                msg = "Loaded successfully.";
            }
            catch (UMLErrorCode e)
            {
                std::cout << UMLException::error_to_string(e) << std::endl;
                msg = "Load failed.";
            }
        }
        
        View->display_msg(msg);
        //API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_json_window();
    });

    // Link add class button to add class event/parsing
    View->ClassSubmit.events().click([&] {
        std::string candidateClassName = View->ClassNameText.text();
        std::string candidateFieldsBlob = View->ClassFields.text();
        std::string candidateMethodsBlob = View->ClassMethods.text();
        if (build_class(candidateClassName, candidateFieldsBlob, candidateMethodsBlob))
        {
            View->display_msg("Successfully added");
        }
        else
        {
            View->display_msg("Class couldn't be added");
        }
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_class_builder_window();
    });

    // Link add relationship button
    View->RelationshipSubmit.events().click([&]{
        std::string candidateClassSrc = View->RelationshipSrc.text();
        std::string candidateClassDest = View->RelationshipDest.text();
        std::string rTypeString = View->RelationshipTypeSelect.text(View->RelationshipTypeSelect.option());
        RelationshipType rType = UMLRelationship::type_from_string(rTypeString);

        if (build_relationship(candidateClassSrc, candidateClassDest, rType))
        {
            View->display_msg("Successfully added");
        }
        else
        {
            View->display_msg("Relationship couldn't be added");
        }
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_relationship_window();
    });

    // Link delete class button
    View->DeleteClassButton.events().click([&] {
        std::string candidateClassName = View->DeleteClassInput.text();
        if (delete_class(candidateClassName))
        {
            View->display_msg("Successfully removed class");
        }
        else
        {
            View->display_msg("Class could not be removed");
        }
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_delete_class_window();
    });

    // Link delete relationship button
    View->DeleteRelButton.events().click([&] {
        std::string candidateSrcName = View->DeleteRelSrcInput.text();
        std::string canddidateDestName = View->DeleteRelDestInput.text();
        if (delete_relationship(candidateSrcName, canddidateDestName))
        {
            View->display_msg("Successfully removed relationship");
        }
        else
        {
            View->display_msg("Relationship could not be removed");
        }
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_delete_relationship_window();
    });

    // Link get class name button
    View->GetClassButton.events().click([&] {
        std::string className = View->GetClassInput.text();
        if (!className.empty())
        {
            edit_class(className);
        }
        else
        {
            View->display_msg("No class name entered.");
        }
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_get_class_window();
    });

    View->EditClassSubmit.events().click([&] {
        std::string classNameBefore = View->GetClassInput.text();
        std::string enteredClassName = View->EditClassNameText.text();
        std::string enteredFieldsBlob = View->EditClassFields.text();
        std::string enteredMethodsBlob = View->EditClassMethods.text();
        edit_class(classNameBefore, enteredClassName, enteredFieldsBlob, enteredMethodsBlob);
        API::window_enabled(View->Form, true);
        View->clear_input_text();
        View->close_edit_class_window();
        View->display_msg("Modified successfully");
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
    else if (userInput == "create_class")
    {
        add_class();
    }
    else if (userInput == "create_relationship")
    {
        add_relationship();
    }
    else if (userInput == "delete_class")
    {
        remove_class();
    }
    else if (userInput == "delete_relationship")
    {
        remove_relationship();
    }
    else if (userInput == "edit_class")
    {
        edit_class();
    }
    else if (userInput == "list_classes")
    {
        View->display_classes();
    }
    else if (userInput == "list_relationships")
    {
        View->display_relationships();
    }
    else if (userInput == "save")
    {
        State = JSONState::SAVE;
        json_window();
    }
    else if (userInput == "load")
    {
        State = JSONState::LOAD;
        json_window();
    }
    else if (userInput == "quit")
    {
        View->stop();
    }
    else
    {
        View->display_msg("Unknown command. Type help for commands");
    }
    View->clear_input_text();
}

void GUIController::json_window()
{
    API::window_enabled(View->Form, false);
    View->display_json_window();
}

void GUIController::add_class()
{
    API::window_enabled(View->Form, false);
    View->display_class_builder_window();
}

bool GUIController::build_class(std::string& className, std::string& fieldsBlob, std::string& methodsBlob)
{
    if (className.empty())
        return false;

    std::vector<ClassField> parsedFields = parse_fields(fieldsBlob);
    std::vector<ClassMethod> parsedMethods = parse_methods(methodsBlob);

    return Model->add_class(className, parsedFields, parsedMethods);
}

std::vector<ClassField> parse_fields(std::string& fieldsBlob)
{
    std::vector<ClassField> result;
    if (!fieldsBlob.empty())
    {
        std::stringstream ss(fieldsBlob);
        std::string line;
        while (std::getline(ss, line, '\n'))
        {
            ClassField field {line};
            result.push_back(field);
        }
    }

    return result;
}

std::vector<ClassMethod> parse_methods(std::string& methodsBlob)
{
    std::vector<ClassMethod> result;
    if (!methodsBlob.empty())
    {
        std::stringstream ss(methodsBlob);
        std::string line;
        while (std::getline(ss, line, '\n'))
        {
            ClassMethod method;
            std::size_t openPos = line.find("(");
            std::size_t closePos = line.find(")");

            std::string methodName = line.substr(0, openPos);
            method.set_method_name(methodName);
            std::string paramString = line.substr(openPos + 1, closePos - 1);
            paramString.pop_back(); // WTF C++ STOP LEAVING A ) im tired

            if (!paramString.empty())
            {
                std::stringstream mss(paramString);
                std::string singleParamName;
                while (std::getline(mss, singleParamName, ' '))
                {
                    MethodParameter parameter{ singleParamName };
                    method.add_parameter(parameter);
                }
            }

            result.push_back(method);
        }
    }
    return result;
}

void GUIController::add_relationship()
{
    API::window_enabled(View->Form, false);
    View->display_relationship_window();
}

bool GUIController::build_relationship(std::string& classSrc, std::string& classDest, RelationshipType relationshipType)
{
    if (classSrc.empty() || classDest.empty())
        return false;
    return Model->add_relationship(classSrc, classDest, relationshipType);
}

void GUIController::remove_class()
{
    API::window_enabled(View->Form, false);
    View->display_delete_class_window();
}

bool GUIController::delete_class(std::string& className)
{
    if (className.empty())
        return false;

    return Model->remove_class(className);
}

void GUIController::remove_relationship()
{
    API::window_enabled(View->Form, false);
    View->display_delete_relationship_window();
}

bool GUIController::delete_relationship(std::string& classSrc, std::string& classDest)
{
    if (classSrc.empty() || classDest.empty())
        return false;
    return Model->remove_relationship(classSrc, classDest);
}

void GUIController::edit_class()
{
    API::window_enabled(View->Form, false);
    View->display_get_class_window();
}

void GUIController::edit_class(std::string className)
{
    UMLClass editingClass;
    Model->get_class_by_name(className, editingClass);
    View->display_edit_class_window(editingClass);
}

void GUIController::edit_class(std::string& classNameBefore, std::string& enteredClassName, 
                                std::string& enteredFieldsBlob, std::string& enteredMethodsBlob)
{
    std::vector<ClassField> parsedFields = parse_fields(enteredFieldsBlob);
    std::vector<ClassMethod> parsedMethods = parse_methods(enteredMethodsBlob);

    UMLClass existingClass;
    Model->get_class_by_name(classNameBefore, existingClass);

    if (existingClass.get_class_name() != enteredClassName)
        Model->modify_class_name(existingClass.get_class_name(), enteredClassName);

    // Iterate through existing fields; if we can't find it from the blob/parsed fields, remove it.
    for (ClassField fieldExisting : existingClass.get_all_fields())
    {
        int count = 0;
        for (ClassField fieldEntered : parsedFields)
        {
            if (fieldExisting.get_field_name() == fieldEntered.get_field_name())
                count++;
        }
        // If we iterated through and didn't find it, remove it from the model
        if (count == 0)
            Model->remove_class_field(enteredClassName, fieldExisting.get_field_name());
    }

    // Same thing but backwards; if we cant find the field from the parsed fields in the existing fields, add it.
    for (ClassField fieldEntered : parsedFields)
    {
        int count = 0;
        for (ClassField fieldExisting : existingClass.get_all_fields())
        {
            if (fieldEntered.get_field_name() == fieldExisting.get_field_name())
                count++;
        }

        if (count == 0)
            Model->add_class_field(enteredClassName, fieldEntered.get_field_name());
    }

    // Do the same as above except with methods.
    for (ClassMethod methodExisting : existingClass.get_all_methods())
    {
        int count = 0;
        for (ClassMethod methodEntered : parsedMethods)
        {
            if (methodExisting.get_method_name() == methodEntered.get_method_name())
                count++;
        }

        if (count == 0)
            Model->remove_class_method(enteredClassName, methodExisting.get_method_name());
    }

    for (ClassMethod methodEntered : parsedMethods)
    {
        int count = 0;
        for (ClassMethod methodExisting : existingClass.get_all_methods())
        {
            if (methodEntered.get_method_name() == methodExisting.get_method_name())
                count++;
        }
        if (count == 0)
            Model->add_class_method(enteredClassName, methodEntered);
    }
}
