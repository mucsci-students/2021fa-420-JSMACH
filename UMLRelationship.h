
#ifndef UMLRELATIONSHIP
#define UMLRELATIONSHIP

#include "UMLClass.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class UMLRelationship {
	private:
		UMLClass* ClassSrc;
		UMLClass* ClassDest;

	public:
		UMLRelationship();
		UMLRelationship(UMLClass& src, UMLClass& dest);
		~UMLRelationship();

		const UMLClass& get_src_class() const;
		const UMLClass& get_dest_class() const;
 
};

void to_json(json& j, const UMLRelationship& ur);
//THERE IS NO FROM JSON.
//Its impossible; json needs to be reinitialized manually from names and utilizing references
#endif