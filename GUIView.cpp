#include "GUIView.h"

#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>

using namespace nana;

GUIView::GUIView(UMLModel& model)
    : Model(&model)
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

    build_json_window();
    build_class_builder_window();
    build_relationship_window();
    build_delete_class_window();
    build_delete_relationship_window();
    build_edit_class_window();
    build_get_class_window();
}

void GUIView::build_json_window()
{
    JSONForm.size(size(300, 50));
    JSONForm.caption("Enter file name");
    JSONWidgets.bind(JSONForm);

    JSONButton.create(JSONForm);
    JSONButton.caption("Go");
    
    JSONInput.create(JSONForm);
    JSONInput.multi_lines(false);
    JSONInput.editable(true);

    JSONWidgets.div("<vert <input weight=50%> <go weight=50%>>");
    JSONWidgets["input"] << JSONInput;
    JSONWidgets["go"] << JSONButton;
    JSONWidgets.collocate();

}

void GUIView::build_class_builder_window()
{
    ClassWindow.size(size(300, 400));
    ClassWindow.caption("Build class");
    ClassWidgets.bind(ClassWindow);

    ClassSubmit.create(ClassWindow);
    ClassSubmit.caption("Go");

    ClassNameText.create(ClassWindow);
    ClassNameText.multi_lines(false);
    ClassNameText.editable(true);
    ClassNameTextLabel.create(ClassWindow);
    ClassNameTextLabel.caption("Class Name:");
    ClassNameTextLabel.text_align(align::center);

    ClassFields.create(ClassWindow);
    ClassFields.multi_lines(true);
    ClassFields.editable(true);
    ClassFieldsLabel.create(ClassWindow);
    ClassFieldsLabel.caption("Fields (enter separated by newline)");
    ClassFieldsLabel.text_align(align::left);

    ClassMethods.create(ClassWindow);
    ClassMethods.multi_lines(true);
    ClassMethods.editable(true);
    ClassMethodsLabel.create(ClassWindow);
    ClassMethodsLabel.caption("Methods (Enter name separated by newline, with parameters in paranthesis)");
    ClassMethodsLabel.text_align(align::left);

    ClassWidgets.div("<vert < <<nametextlabel weight=80> <nametext weight=220> gap=2> weight=25> <vert <fieldslabel weight=20> <fields weight=100>> <vert <methodslabel weight=40> <methods weight=100>> <submit weight=25>>");
    ClassWidgets["nametext"] << ClassNameText;
    ClassWidgets["nametextlabel"] << ClassNameTextLabel;
    ClassWidgets["fieldslabel"] << ClassFieldsLabel;
    ClassWidgets["fields"] << ClassFields;
    ClassWidgets["methodslabel"] << ClassMethodsLabel;
    ClassWidgets["methods"] << ClassMethods;
    ClassWidgets["submit"] << ClassSubmit;
    ClassWidgets.collocate();
}

void GUIView::build_relationship_window()
{
    RelationshipWindow.size(size(300, 150));
    RelationshipWindow.caption("Build relationship");
    RelationshipWidgets.bind(RelationshipWindow);

    RelationshipSubmit.create(RelationshipWindow);
    RelationshipSubmit.caption("Go");

    RelationshipSrc.create(RelationshipWindow);
    RelationshipSrc.multi_lines(false);
    RelationshipSrc.editable(true);
    SrcLabel.create(RelationshipWindow);
    SrcLabel.caption("Enter source class name");

    RelationshipDest.create(RelationshipWindow);
    RelationshipDest.multi_lines(false);
    RelationshipDest.editable(true);
    DestLabel.create(RelationshipWindow);
    DestLabel.caption("Enter destination class name");

    RelationshipTypeSelect.create(RelationshipWindow);
    RelationshipTypeSelect.editable(false);
    RelationshipTypeSelect.push_back("Aggregation");
    RelationshipTypeSelect.push_back("Composition");
    RelationshipTypeSelect.push_back("Inheritance");
    RelationshipTypeSelect.push_back("Realization");

    RelationshipWidgets.div("<vert <<srclabel weight=30%> <srcname weight=70%> weight=50> <<destlabel weight=30%> <destname weight=70%> weight=50> <type weight=20> <submit weight=20> gap=5>");
    RelationshipWidgets["srclabel"] << SrcLabel;
    RelationshipWidgets["srcname"] << RelationshipSrc;
    RelationshipWidgets["destlabel"] << DestLabel;
    RelationshipWidgets["destname"] << RelationshipDest;
    RelationshipWidgets["type"] << RelationshipTypeSelect;
    RelationshipWidgets["submit"] << RelationshipSubmit;
    RelationshipWidgets.collocate();
}

void GUIView::build_delete_class_window()
{
    DeleteClassWindow.size(size(300, 50));
    DeleteClassWindow.caption("Enter name of class");
    DeleteClassWidgets.bind(DeleteClassWindow);

    DeleteClassButton.create(DeleteClassWindow);
    DeleteClassButton.caption("Remove");

    DeleteClassInput.create(DeleteClassWindow);
    DeleteClassInput.multi_lines(false);
    DeleteClassInput.editable(true);

    DeleteClassWidgets.div("<vert <input weight=25> <go weight=25>>");
    DeleteClassWidgets["input"] << DeleteClassInput;
    DeleteClassWidgets["go"] << DeleteClassButton;
    DeleteClassWidgets.collocate();
}

void GUIView::build_delete_relationship_window()
{
    DeleteRelWindow.size(size(300, 75));
    DeleteRelWindow.caption("Enter name of classes to delete");
    DeleteRelWidgets.bind(DeleteRelWindow);

    DeleteRelButton.create(DeleteRelWindow);
    DeleteRelButton.caption("Remove");

    DeleteRelSrcInput.create(DeleteRelWindow);
    DeleteRelSrcInput.multi_lines(false);
    DeleteRelSrcInput.editable(true);
    DeleteRelSrcLabel.create(DeleteRelWindow);
    DeleteRelSrcLabel.caption("Source");

    DeleteRelDestInput.create(DeleteRelWindow);
    DeleteRelDestInput.multi_lines(false);
    DeleteRelDestInput.editable(true);
    DeleteRelDestLabel.create(DeleteRelWindow);
    DeleteRelDestLabel.caption("Destination");

    DeleteRelWidgets.div("<vert <<srclabel> <inputsrc> weight=25> <<destlabel> <inputdest> weight=25> <go weight=25>>");
    DeleteRelWidgets["srclabel"] << DeleteRelSrcLabel;
    DeleteRelWidgets["inputsrc"] << DeleteRelSrcInput;
    DeleteRelWidgets["destlabel"] << DeleteRelDestLabel;
    DeleteRelWidgets["inputdest"] << DeleteRelDestInput;
    DeleteRelWidgets["go"] << DeleteRelButton;
    DeleteRelWidgets.collocate();
}

void GUIView::build_edit_class_window()
{
    EditClassWindow.size(size(300, 400));
    EditClassWindow.caption("Modify Class");
    EditClassWidgets.bind(EditClassWindow);

    EditClassSubmit.create(EditClassWindow);
    EditClassSubmit.caption("Go");

    EditClassNameText.create(EditClassWindow);
    EditClassNameText.multi_lines(false);
    EditClassNameText.editable(true);
    EditClassNameTextLabel.create(EditClassWindow);
    EditClassNameTextLabel.caption("Class Name:");
    EditClassNameTextLabel.text_align(align::center);

    EditClassFields.create(EditClassWindow);
    EditClassFields.multi_lines(true);
    EditClassFields.editable(true);
    EditClassFieldsLabel.create(EditClassWindow);
    EditClassFieldsLabel.caption("Fields (enter separated by newline)");
    EditClassFieldsLabel.text_align(align::left);

    EditClassMethods.create(EditClassWindow);
    EditClassMethods.multi_lines(true);
    EditClassMethods.editable(true);
    EditClassMethodsLabel.create(EditClassWindow);
    EditClassMethodsLabel.caption("Methods (Enter name separated by newline, with parameters in paranthesis)");
    EditClassMethodsLabel.text_align(align::left);

    EditClassWidgets.div("<vert < <<nametextlabel weight=80> <nametext weight=220> gap=2> weight=25> <vert <fieldslabel weight=20> <fields weight=100>> <vert <methodslabel weight=40> <methods weight=100>> <submit weight=25>>");
    EditClassWidgets["nametext"] << EditClassNameText;
    EditClassWidgets["nametextlabel"] << EditClassNameTextLabel;
    EditClassWidgets["fieldslabel"] << EditClassFieldsLabel;
    EditClassWidgets["fields"] << EditClassFields;
    EditClassWidgets["methodslabel"] << EditClassMethodsLabel;
    EditClassWidgets["methods"] << EditClassMethods;
    EditClassWidgets["submit"] << EditClassSubmit;
    EditClassWidgets.collocate();
}

void GUIView::build_get_class_window()
{
    GetClassWindow.size(size(300, 50));
    GetClassWindow.caption("Enter name of class");
    GetClassWidgets.bind(GetClassWindow);

    GetClassButton.create(GetClassWindow);
    GetClassButton.caption("Find");

    GetClassInput.create(GetClassWindow);
    GetClassInput.multi_lines(false);
    GetClassInput.editable(true);

    GetClassWidgets.div("<vert <input weight=25> <go weight=25>>");
    GetClassWidgets["input"] << GetClassInput;
    GetClassWidgets["go"] << GetClassButton;
    GetClassWidgets.collocate();
}

void GUIView::display_json_window()
{
    JSONForm.show();
}

void GUIView::close_json_window()
{
    JSONForm.hide();
    JSONInput.reset();
}

void GUIView::display_class_builder_window()
{
    ClassWindow.show();
}

void GUIView::close_class_builder_window()
{
    ClassNameText.reset();
    ClassFields.reset();
    ClassMethods.reset();
    ClassWindow.hide();
}

void GUIView::display_relationship_window()
{
    RelationshipWindow.show();
}

void GUIView::close_relationship_window()
{
    RelationshipDest.reset();
    RelationshipSrc.reset();
    RelationshipWindow.hide();
}

void GUIView::display_delete_class_window()
{
    DeleteClassWindow.show();
}

void GUIView::close_delete_class_window()
{
    DeleteClassInput.reset();
    DeleteClassWindow.close();
}

void GUIView::display_delete_relationship_window()
{
    DeleteRelDestInput.reset();
    DeleteRelSrcInput.reset();
    DeleteRelWindow.show();
}

void GUIView::close_delete_relationship_window()
{
    DeleteRelSrcInput.reset();
    DeleteRelDestInput.reset();
    DeleteRelWindow.hide();
}

void GUIView::display_get_class_window()
{
    GetClassWindow.show();
}

void GUIView::close_get_class_window()
{
    GetClassWindow.hide();
}

void GUIView::display_edit_class_window(UMLClass& current)
{
    EditClassNameText.caption(current.get_class_name());

    std::vector<ClassField> fields = current.get_all_fields();
    std::string fieldsBlob;
    for (ClassField field : fields)
    {
        fieldsBlob.append(field.get_field_name() + "\n");
    }
    EditClassFields.caption(fieldsBlob);

    std::vector<ClassMethod> methods = current.get_all_methods();
    std::string methodsBlob;
    for (ClassMethod method : methods)
    {
        methodsBlob.append(method.get_method_name() + "(");
        std::list<MethodParameter> params = method.get_parameters();
        for (MethodParameter param : params)
        {
            methodsBlob.append(param.get_name() + " ");
        }
        methodsBlob.append(")\n");
    }
    EditClassMethods.caption(methodsBlob);

    EditClassWindow.show();
}

void GUIView::close_edit_class_window()
{
    EditClassWindow.hide();
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

void GUIView::display_classes()
{
    std::list<std::string> classesNames = Model->get_all_class_names();
    std::string result;
    if (classesNames.size() != 0)
    {
        for (std::string name : classesNames)
        {
            UMLClass singleClass;
            if (Model->get_class_by_name(name, singleClass))
            {
                std::string classAsString = single_class_as_string(singleClass);
                result.append(classAsString);
            }
        }
    }
    else
    {
        result = "You have no classes.";
    }

    display_msg(result);
}

std::string GUIView::single_class_as_string(UMLClass& currentClass)
{
    std::string className = currentClass.get_class_name();
    std::vector<ClassField> fields = currentClass.get_all_fields();
    std::vector<ClassMethod> methods = currentClass.get_all_methods();

    std::string result = "CLASS: " + className + " {\n\tFields:\n";

    for (unsigned int i = 0; i < fields.size(); i++)
    {
        result.append("\t\t");
        result.append(fields[i].get_field_name());
        result.append("\n");
    }

    result.append("\tMethods:\n");
    for (unsigned int i = 0; i < methods.size(); i++)
    {
        std::string method = "\t\t";
        method.append(methods[i].get_method_name());
        method.append("(");
        std::list<MethodParameter> parameters = methods[i].get_parameters();
        for (MethodParameter param : parameters)
        {
            method.append(param.get_name());
            method.append(" ");
        }
        method.append(")");
        result.append(method);
        result.append("\n");
    }
    result.append("}\n");
    return result;
}

void GUIView::display_relationships()
{
    std::list<UMLRelationship> relationships = Model->get_all_relationships();
    if (relationships.size() == 0)
    {
        display_msg("You have no relationships.");
    }
    else
    {
        std::string result;
        for (UMLRelationship rel : relationships)
        {
            result.append(single_relationship_as_string(rel));
        }

        display_msg(result);
    }
}

std::string GUIView::single_relationship_as_string(UMLRelationship& currentRelationship)
{
    std::string result;
    std::string rType = currentRelationship.type_to_string();
    std::string src = currentRelationship.get_src_class().get_class_name();
    std::string dest = currentRelationship.get_dest_class().get_class_name();
    result.append("TYPE: \n\t");
    result.append(rType.append("\n"));
    
    result.append("SOURCE: \n\t");
    result.append(src.append("\n"));

    result.append("DESTINATION: \n\t");
    result.append(dest.append("\n"));

    result.append("\n");
    return result;
}

void GUIView::run()
{
    // Shows form and run
    Form.show();
    nana::exec();
}

void GUIView::stop()
{
    nana::API::exit();
}