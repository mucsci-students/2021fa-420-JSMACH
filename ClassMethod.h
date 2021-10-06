#ifndef CLASSMETHOD
#define CLASSMETHOD

#include <string>
#include <list>
#include "MethodParameter.h"

class ClassMethod {
    private:
        std::string ClassMethodName;
        std::list <MethodParameter> MethodParameters;

        std::list<MethodParameter>::iterator get_param_iter_by_name(const std::string& paramName);

    public:

        ClassMethod();

        // No method parameters constructor
        ClassMethod(std::string name);

        // Method name and parameters constructor
        ClassMethod(std::string name, std::list<MethodParameter> parameters);
        ~ClassMethod();

        // Getter for method name
        std::string get_method_name() const;
        // Setter for method name
        void set_method_name(const std::string& name);

        // Gets a const list of all the method parameters in the current method
        // Could return empty list if there are no parameters
        const std::list <MethodParameter> get_parameters() const;

        // Adds a MethodParameter object to the method parameter list
        // Returns true if successful
        // Returns false in cases where the object already exists (by name)
        bool add_parameter(MethodParameter parameter);

        // Removes a parameter from the curret object method by name
        // Returns true if successful
        // Returns false if the parameter doesn't exist
        bool remove_parameter(const std::string& paramName);

        // Renames a parameter from the "nameFrom" name to the "nameTo" name
        // Returns true if successful
        // Returns false if either the "nameFrom" doesn't exist or the "nameTo" already exists
        bool rename_parameter(const std::string& nameFrom, const std::string& nameTo);

        bool does_parameter_exist(const std::string& paramName);
};

void to_json(json& j, const ClassMethod& cm);
void from_json(const json& j, ClassMethod& cm);

#endif