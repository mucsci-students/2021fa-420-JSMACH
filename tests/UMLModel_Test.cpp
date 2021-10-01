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

    // Name and vector of attributes
    std::vector <UMLAttribute> myAttributes {{"MyAttribute1"}, {"MyAttribute2"}};
    model.add_class("MyClass2", myAttributes);
    
    // Derived from a new UMLClass object
    UMLClass newClass {"MyClass3", {{"MyAttribute1"}, {"MyAttribute2"}}};
    model.add_class(newClass);

    SECTION("Overloads for adding classes all work")
    {
        REQUIRE(model.does_class_exist("MyClass1") == true);
        REQUIRE(model.does_class_exist("MyClass2") == true);
        REQUIRE(model.does_class_exist("MyClass3") == true);
    }

    SECTION("Methods that modify classes work")
    {
        REQUIRE(model.modify_class_name("MyClass1", "MyCoolClass") == true);
        REQUIRE(model.does_class_exist("MyCoolClass") == true);
        REQUIRE(model.does_class_exist("MyClass1") == false);

        UMLAttribute newAttribute {"NewAttribute"};
        REQUIRE(model.add_class_attribute("MyClass3", newAttribute) == true);
        REQUIRE(model.remove_class_attribute("MyClass3", "MyAttribute1") == true);

        UMLClass class3Copy;
        REQUIRE(model.get_class_by_name("MyClass3", class3Copy) == true);
        REQUIRE(class3Copy.does_attribute_already_exist("NewAttribute") == true);
        REQUIRE(class3Copy.does_attribute_already_exist("MyAttribute1") == false);
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