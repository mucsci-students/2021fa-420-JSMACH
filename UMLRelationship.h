
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include "UMLClass.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLRelationship {
	private:
		UMLClass ClassSrc;
		UMLClass ClassDest;

	public:
		UMLRelationship();
		UMLRelationship(UMLClass src, UMLClass dest);
		~UMLRelationship();

		UMLClass& get_src_class();
		UMLClass& get_dest_class();

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(UMLRelationship, ClassSrc, ClassDest);
};

//void to_json(json& j, const UMLRelationship& ur);
//void from_json(json& j, const UMLRelationship& ur);
#endif