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
    no_such_relationship_type
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
                default:
                    return "Unknown error code; The UMLErrorCode was probably defined but the to string method was not updated";
            }
        }
};

#endif