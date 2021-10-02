#ifndef METHODPARAMETER
#define METHODPARAMETER

#include <string>


class MethodParameter {
	private:
		std::string ParameterName;

	public:
		MethodParameter(std::string paramName);
		~MethodParameter();

		std::string get_name();
		void set_name(std::string newName);
};

#endif