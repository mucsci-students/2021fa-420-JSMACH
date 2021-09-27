
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include "UMLClass.h"
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum class RelationshipType {
	Aggregation,
	Composition,
	Inheritance,
	Realization
};

class UMLRelationship {
	private:
		UMLClass* ClassSrc;
		UMLClass* ClassDest;
		RelationshipType Type;

	public:
		UMLRelationship();
		UMLRelationship(UMLClass& src, UMLClass& dest);
		UMLRelationship(UMLClass& src, UMLClass& dest, RelationshipType type);
		~UMLRelationship();

		const UMLClass& get_src_class() const;
		const UMLClass& get_dest_class() const;

		std::string type_to_string();
		static RelationshipType type_from_string(std::string typeName);
		bool set_type(std::string);
 
};

void to_json(json& j, const UMLRelationship& ur);
//THERE IS NO FROM JSON.
//Its impossible; json needs to be reinitialized manually from names and utilizing references
#endif