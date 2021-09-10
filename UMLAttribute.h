
#ifndef UMLATTRIBUTE
#define UMLATTRIBUTE

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLAttribute {
	private:
		std::string AttributeName;

	public:
		UMLAttribute(std::string name);
		std::string get_attribute_name() const;

		void set_attribute_name(std::string newName);
};

void to_json(json& j, const UMLAttribute& ua);
void from_json(json& j, const UMLAttribute& ua);
#endif