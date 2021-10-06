#ifndef METHODPARAMETER
#define METHODPARAMETER

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MethodParameter {
	private:
		std::string ParameterName;

	public:
		MethodParameter();
		MethodParameter(std::string paramName);
		~MethodParameter();

		std::string get_name() const;
		void set_name(std::string newName);
};

void to_json(json& j, const MethodParameter& mp);
void from_json(const json& j, MethodParameter& mp);

#endif