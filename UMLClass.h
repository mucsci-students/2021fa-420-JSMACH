
#ifndef UMLCLASS 
#define UMLCLASS

#include <string>
#include <vector>
#include "UMLAttribute.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLClass{
	private:
		std::string ClassName;
		std::vector<UMLAttribute> ClassAttributes;

		std::vector<UMLAttribute>::iterator get_iterator_to_attribute_name(std::string attributeName);
		bool does_attribute_already_exist(std::string attributeName);

	public:
		UMLClass();
		UMLClass(std::string name);
		UMLClass(std::string name, std::vector<UMLAttribute> attributes);
		~UMLClass();

		std::string get_class_name() const;
		void set_class_name(std::string newName);

		std::vector<UMLAttribute> get_all_attributes() const;
		bool add_attribute(UMLAttribute attribute);
		bool remove_attribute(std::string);

		bool operator==(const UMLClass& u) const;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(UMLClass, ClassName, ClassAttributes);

};

//void to_json(json& j, const UMLClass& uc);
//void from_json(json& j, const UMLClass& uc);
#endif