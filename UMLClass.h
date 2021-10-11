
#ifndef UMLCLASS 
#define UMLCLASS

#include <string>
#include <vector>
#include "ClassField.h"
#include "ClassMethod.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLClass{
	private:
		std::string ClassName;
		std::vector<ClassField> Fields;
		std::vector<ClassMethod> Methods;

		std::vector<ClassField>::iterator get_iterator_to_field_name(std::string fieldName);
		std::vector<ClassMethod>::iterator get_iterator_to_method_name(std::string methodName);


	public:
		UMLClass();
		UMLClass(std::string name);

		UMLClass(std::string name, std::vector<ClassField> fields, std::vector<ClassMethod> methods);

		~UMLClass();

		std::string get_class_name() const;
		void set_class_name(std::string newName);

		/*
			FIELD OPERATIONS
		*/

		// Gets a constant vector of all the fields of a class
		std::vector<ClassField> get_all_fields() const;

		// Adds a field to the class object
		// Returns true if the add was successful
		// Returns false if the field name already exists (by name)
		bool add_field(ClassField field);

		// Removes field from the class object
		// Returns true if remove was successful
		// Returns false if the field name didn't exist
		bool remove_field(std::string fieldName);

		// Renames field object on class object
		// Returns true if the rename was successful
		// Returns false if either the "fieldNameFrom" field didn't exist or
		// the "fieldNameTo" already exists
		bool rename_field(std::string fieldNameFrom, std::string fieldNameTo);

		// Method for seeing if a fieldName already exists on a class
		// Returns true if the field already exists, false otherwise.
		bool does_field_already_exist(std::string fieldName);

		/*
			METHOD OPERATIONS
		*/

		// Gets a const vector of all the methods on a class object
		std::vector<ClassMethod> get_all_methods() const;

		// Adds a method object to the current class object
		// Returns true if the add was successful
		// Returns false if the method already exists by name
		bool add_method(ClassMethod method);

		// Removes a method object by name from the current class object
		// Returns true if the remove was successful
		// Returns false if the method doesn't exist by name.
		bool remove_method(std::string methodName);

		// Renames a method object by methodNameFrom to methodNameTo
		// Returns true if the rename was successful
		// Returns false if the methodNameFrom didnt exist or the
		// methodNameTo already exists
		bool rename_method(std::string methodNameFrom, std::string methodNameTo);

		// Sees if a method already exists by name
		// Return true if it exists, false otherwise.
		bool does_method_already_exist(std::string methodName);

		/*
			METHOD PARAMETER OPERATIONS
		*/

		// Adds a parameter to the given method name
		// Returns true if the add was successful
		// Returns false if either the methodname didnt exist or the method object rejected the method parameter object
		bool add_method_parameter(std::string methodName, MethodParameter methodParam);

		// Removes a parameter from the given method name
		// Returns true if the remove was successful
		// Returns false if either the methodName didn't exist or the methodParamName didn't exist
		bool remove_method_parameter(std::string methodName, std::string methodParamName);

		// Renames a parameter on methodName from methodParamNameFrom to methodParamNameTo
		// Returns true if the rename was succesful
		// Returns false if either the methodName didnt exist or the method object rejected either the nameFrom or nameTo
		bool rename_method_parameter(std::string methodName, std::string methodParamNameFrom, std::string methodParamNameTo);

		bool does_method_parameter_exist(std::string methodName, std::string methodParamName);



		bool operator==(const UMLClass& u) const;

};

void to_json(json& j, const UMLClass& uc);
void from_json(const json& j, UMLClass& uc);
#endif