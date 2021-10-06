#ifndef UMLEXCEPTION
#define UMLEXCEPTION

#include <string>

/*
    Error codes that may be thrown in various methods and classes.
    Error codes are accessed (as long as you have the UMLException.hpp header) with the syntax:
    
        throw UMLErrorCode::no_such_relationship_type;

    This can then be caught by a try/catch block: 

        ...
        catch(UMLErrorCode e)
        {
            //do something with the error code
            ...
        }
*/
enum class UMLErrorCode
{
    no_such_relationship_type,
    invalid_json_file,
    file_does_not_exist,
    json_load_error
};

class UMLException
{
    public: 
        /*
            A static method for converting error codes to meaningful error messages.
            This static method is accessed with this syntax:

            UMLException::error_to_string(e)
        */
        static std::string error_to_string(UMLErrorCode e)
        {
            switch(e)
            {
                case UMLErrorCode::no_such_relationship_type:
                    return "A relationship with the specified type/value does not exist";
                case UMLErrorCode::invalid_json_file:
                    return "The json save attempting to be loaded is not valid";
                case UMLErrorCode::file_does_not_exist:
                    return "No file by the name specified was found";
                case UMLErrorCode::json_load_error:
                    return "Something went wrong when trying to load json data";
                default:
                    return "Unknown error code; The UMLErrorCode was probably defined but the to string method was not updated";
            }
        }
};

#endif