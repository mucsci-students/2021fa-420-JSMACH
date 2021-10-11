#include <catch2/catch.hpp>
#include "../UMLClass.h"
#include <vector>

TEST_CASE("Class requirements enforced")
{
    
    //create vector of fields
    ClassField field1 {"field1"};
    ClassField field2 {"field2"};
    std::vector <ClassField> fields;
    fields.push_back(field1);
    fields.push_back(field2);

    //make methodParams list
    std::list <MethodParameter> methodParams;
    MethodParameter param1 {"param1"};
    MethodParameter param2 {"param2"};
    methodParams.push_back(param1);
    methodParams.push_back(param2);

    //make method list; one method without params and one with methodParams list
    ClassMethod method1 {"methodNoParams"};
    ClassMethod method2 {"methodWithParams", methodParams};
    std::vector <ClassMethod> methods;
    methods.push_back(method1);
    methods.push_back(method2);

    //classes without fields or methods
    UMLClass class1{"class1", {}, {}};
    UMLClass class2{"class2", {}, {}};

    //classes with fields, no methods
    UMLClass class3{"class3", fields, {}};
    UMLClass class4{"class4", fields, {}};

    //classes with methods, no fields
    UMLClass class5{"class5", {}, methods};
    UMLClass class6{"class6", {}, methods};

    //class with fields and methods
    UMLClass class7{"class7", fields, methods};


    SECTION("Multiple cases of adding/deleting fields")
    {
        //add to class without fields or methods
        class1.add_field(field1);
        class1.add_field(field2);
        
        //add to class that already has methods
        class5.add_field(field1);
        class5.add_field(field2);

        REQUIRE(class1.does_field_already_exist(field1.get_field_name()) == true);
        REQUIRE(class1.does_field_already_exist(field2.get_field_name()) == true);
        REQUIRE(class5.does_field_already_exist(field1.get_field_name()) == true);
        REQUIRE(class5.does_field_already_exist(field2.get_field_name()) == true);

        //try to add duplicate field
        REQUIRE(class3.add_field(field1) == false);

        //remove fields from classes initialized with fields
        class3.remove_field(field2.get_field_name());
        class7.remove_field(field1.get_field_name());

        //check field was removed
        REQUIRE(class3.does_field_already_exist(field2.get_field_name()) == false);
        REQUIRE(class7.does_field_already_exist(field1.get_field_name()) == false);

    }

    SECTION("Multiple cases of adding/deleting methods")
    {
        //add to class without fields or methods
        class2.add_method(method1);
        class2.add_method(method2);

        //add to class that already has fields
        class4.add_method(method1);
        class4.add_method(method2);

        REQUIRE(class2.does_method_already_exist(method1.get_method_name()) == true);
        REQUIRE(class2.does_method_already_exist(method2.get_method_name()) == true);
        REQUIRE(class4.does_method_already_exist(method1.get_method_name()) == true);
        REQUIRE(class4.does_method_already_exist(method2.get_method_name()) == true);

        //try to add duplicate method
        REQUIRE(class6.add_method(method1) == false);

        //remove methods from classes initialized with methods
        class6.remove_method(method1.get_method_name());
        class7.remove_method(method2.get_method_name());

        REQUIRE(class6.does_method_already_exist(method1.get_method_name()) == false);
        REQUIRE(class7.does_method_already_exist(method2.get_method_name()) == false);

    }

}