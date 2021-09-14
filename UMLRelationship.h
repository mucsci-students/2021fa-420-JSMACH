
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include <string>
#include "UMLClass.h"

class UMLRelationship {
	private:
		std::string RelationshipName;
		UMLClass ClassSrc;
		UMLClass ClassDest;

	public:
		UMLRelationship(std::string name, UMLClass src, UMLClass dest);
		~UMLRelationship();

		std::string get_relationship_name();
		UMLClass get_src_class();
		UMLClass get_dest_class();
};
#endif