
#ifndef UMLATTRIBUTE
#define UMLATTRIBUTE

#include <string>

class UMLAttribute {
	private:
		std::string AttributeName;

	public:
		UMLAttribute(std::string name);
		std::string get_attribute_name();

		void set_attribute_name(std::string newName);
};
#endif