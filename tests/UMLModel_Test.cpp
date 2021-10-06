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
    model.add_class("MyClass3");
    model.add_class("MyClass4");

    //just src and dest
    model.add_relationship("MyClass1", "MyClass2", RelationshipType::Aggregation);

    //recursive
    model.add_relationship("MyClass1", "MyClass1", RelationshipType::Realization);

    //src, dest, type
    model.add_relationship("MyClass2", "MyClass3", RelationshipType::Aggregation);
    model.add_relationship("MyClass3", "MyClass4", RelationshipType::Composition);

    RelationshipType inh = UMLRelationship::type_from_string("inHerItaNce");
    RelationshipType real = UMLRelationship::type_from_string("REALIZATION");
   
    //src, dest, type (checking for case insensitivity)
    model.add_relationship("MyClass4", "MyClass3", inh);
    model.add_relationship("MyClass3", "MyClass2", real);

    SECTION("Adding relationships")
    {
        //src and dest
        REQUIRE(model.does_relationship_exist("MyClass1", "MyClass2") == true);
        REQUIRE(model.does_relationship_exist("MyClass1", "MyClass1") == true);

        //src, dest, type
        REQUIRE(model.does_relationship_exist("MyClass2", "MyClass3") == true);
        REQUIRE(model.does_relationship_exist("MyClass3", "MyClass4") == true);
        REQUIRE(model.does_relationship_exist("MyClass4", "MyClass3") == true);
        REQUIRE(model.does_relationship_exist("MyClass3", "MyClass2") == true);   
    }

    SECTION("Modifying relationships and relationships reflect class changes")
    {
        model.remove_class("MyClass1");

        //ensure removing class removes relationship
        REQUIRE(model.does_relationship_exist("MyClass1", "MyClass2") == false);
        REQUIRE(model.does_relationship_exist("MyClass1", "MyClass1") == false);

        model.remove_relationship("MyClass2", "MyClass3");

        //ensure remove
        REQUIRE(model.does_relationship_exist("MyClass2", "MyClass3") == false);

        //no duplicates
        REQUIRE(model.add_relationship("MyClass3", "MyClass4", RelationshipType::Composition) == false);

        model.modify_class_name("MyClass3", "NewClassName");

        //rename class is reflected
        REQUIRE(model.does_relationship_exist("MyClass3", "MyClass4") == false);
        REQUIRE(model.does_relationship_exist("NewClassName", "MyClass4") == true);

    }
 
/* TEST_CASE("Requirements for UMLClass enforced")
{
    UMLClass myClass;

    model.add_class(myClass);

    SECTION("")
    {
        
        
        //no duplicate class name
        REQUIRE(model.add_class("MyClass1") == false);

        model.remove_class("MyClass1");

        //remove class
        REQUIRE(model.does_class_exist("MyClass1") == false);
        
    }

}
*/

}