#include <catch2/catch.hpp>
#include <vector>
#include "../UMLClass.h"
#include "../UMLAttribute.h"
#include "../UMLRelationship.h"
#include "../UMLModel.h"

TEST_CASE("Class related operations in the UMLModel")
{
    UMLModel model;

    // Just name
    model.add_class("MyClass1");

    // Name and vector of fields and methods
    std::vector <ClassField> myFields{ {"MyField1"}, {"MyField2"}, {"MyField3"} };

    ClassMethod method1 { "MethodNoParameters" };
    ClassMethod method2 { "MethodWithParameters" };
    MethodParameter param1 { "MyParam1" };
    MethodParameter param2 { "MyParam2" };

    method2.add_parameter(param1);
    method2.add_parameter(param2);

    std::vector <ClassMethod> myMethods;
    myMethods.push_back(method1);
    myMethods.push_back(method2);

    model.add_class("MyClass2", myFields, myMethods);
    
    // Derived from a new UMLClass object
    UMLClass newClass{ "MyClass3", {}, {} };
    model.add_class(newClass);

    SECTION("Overloads for adding classes all work")
    {
        REQUIRE(model.does_class_exist("MyClass1") == true);
        REQUIRE(model.does_class_exist("MyClass2") == true);
        REQUIRE(model.does_class_exist("MyClass3") == true);
    }

    SECTION("Methods that modify classes work")
    {
        // Ensure they get added
        REQUIRE(model.modify_class_name("MyClass1", "MyCoolClass") == true);
        REQUIRE(model.does_class_exist("MyCoolClass") == true);
        REQUIRE(model.does_class_exist("MyClass1") == false);

        model.modify_class_name("MyCoolClass", "MyClass1");

        // Fields
        ClassField newField{ "AnotherField" };
        REQUIRE(model.add_class_field("MyClass3", newField) == true);
        REQUIRE(model.does_class_have_field("MyClass3", newField.get_field_name()) == true);
        REQUIRE(model.remove_class_field("MyClass3", newField.get_field_name()) == true);
        REQUIRE(model.does_class_have_field("MyClass3", newField.get_field_name()) == false);

        // Methods
        ClassMethod newMethod{ "AnotherMethod" };
        REQUIRE(model.add_class_method("MyClass1", newMethod) == true);
        REQUIRE(model.does_class_have_method("MyClass1", "AnotherMethod") == true);
        REQUIRE(model.rename_class_method("MyClass1", "AnotherMethod", "TheSameMethodAgain") == true);

        REQUIRE(model.does_class_have_method("MyClass1", "AnotherMethod") == false);
        REQUIRE(model.does_class_have_method("MyClass1", "TheSameMethodAgain") == true);
        REQUIRE(model.remove_class_method("MyClass1", "TheSameMethodAgain") == true);
        REQUIRE(model.does_class_have_method("MyClass1", "TheSameMethodAgain") == false);

        // Duplicate field and method names aren't allowed:
        ClassField duplicateField{ "MyField1" };
        ClassMethod duplicateMethod{ "MethodNoParameters" };
        REQUIRE(model.add_class_field("MyClass2", duplicateField) == false);
        REQUIRE(model.add_class_method("MyClass2", duplicateMethod) == false);

    }
}

TEST_CASE("Relationship related operations in the UMLModel")
{
    UMLModel model;

    model.add_class("MyClass1");
    model.add_class("MyClass2");

    model.add_relationship("MyClass1", "MyClass2");

    SECTION("Ensure relationships exist")
    {
        REQUIRE(model.does_relationship_exist("MyClass1", "MyClass2") == true);
        //make sure delete class
        //make sure no duplicate
        //recursive
        //delete relationship
        //delete class
        //rename class is reflected
    }

    
}