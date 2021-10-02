
#ifndef CLASSFIELD
#define CLASSFIELD

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ClassField {

	private:
		std::string FieldName;

	public:

		ClassField(std::string name);
        ~ClassField();
		// Getter for the field name
		std::string get_field_name() const;

		// Setter for the field name
		void set_field_name(std::string newName);
};

//void to_json(json& j, const ClassField& ua);
//void from_json(json& j, const ClassField& ua);
#endif