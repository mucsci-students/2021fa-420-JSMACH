
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include <string>
#include "UMLClass.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLRelationship {
	private:
		std::string RelationshipName;
		UMLClass ClassSrc;
		UMLClass ClassDest;

	public:
		UMLRelationship();
		UMLRelationship(std::string name, UMLClass src, UMLClass dest);
		~UMLRelationship();

		std::string get_relationship_name() const;
		UMLClass get_src_class() const;
		UMLClass get_dest_class() const;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(UMLRelationship, RelationshipName, ClassSrc, ClassDest);
};

//void to_json(json& j, const UMLRelationship& ur);
//void from_json(json& j, const UMLRelationship& ur);
#endif