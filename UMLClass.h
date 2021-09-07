
#ifndef UMLCLASS 
#define UMLCLASS

#include <string>
#include <vector>
#include <UMLRelationship.h>
#include <UMLAttribute.h>

class UMLClass{
	private:
		std::string ClassName;
		std::vector<UMLRelationship> ClassRelationships;
		std::vector<UMLAttribute> ClassAttributes;

	public:
		std::string get_class_name();
};
#endif