
#ifndef CLASSMETHOD
#define CLASSMETHOD

#include <string>
#include <list>

class ClassMethod {
    private:
        std::string ClassMethodName;
        std::list <std::string> ClassParameters;

        std::list<std::string>::iterator get_param_iter_by_name(const std::string& paramName);
        bool does_parameter_exist(const std::string& paramName);
        std::string get_param_name();
        void set_param_name(std::string newName);

    public:
        ClassMethod(std::string name);
        ClassMethod(std::string name, std::list<std::string> parameters);
        ~ClassMethod();

        std::string get_method_name() const;
        void set_method_name(const std::string& name);

        const std::list <std::string> get_parameters() const;
        bool add_parameter(const std::string& paramName);
        bool remove_parameter(const std::string& paramName);
        bool rename_parameter(const std::string& nameFrom, const std::string& nameTo);
};

#endif