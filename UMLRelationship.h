
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include <string>
#include <UMLClass.h>

class UMLRelationship {
	private:
		std::string RelationshipName;
		UMLClass& ClassSrc;
		UMLClass& ClassDest;

	public:
		std::string get_relationship_name();
};
#endif