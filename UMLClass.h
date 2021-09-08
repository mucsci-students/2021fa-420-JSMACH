
#ifndef UMLCLASS 
#define UMLCLASS

#include <string>
#include <vector>
#include "UMLAttribute.h"

class UMLClass{
	private:
		std::string ClassName;
		std::vector<UMLAttribute> ClassAttributes;

	public:
		UMLClass(std::string name);
		UMLClass(std::string name, std::vector<UMLAttribute> attributes);
		~UMLClass();

		std::string get_class_name();
		void set_class_name(std::string newName);

		std::vector<UMLAttribute> get_all_attributes();
		bool add_attribute(UMLAttribute attribute);
		bool remove_attribute(UMLAttribute attribute);

		bool operator==(const UMLClass& u) const;

};
#endif