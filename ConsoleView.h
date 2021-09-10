#ifndef UML_CONSOLE_VIEW
#define UML_CONSOLE_VIEW

/*
    The ConsoleView is responsible for displaying information to the user.
    Very little if any application logic is handled in the view class.
*/
class ConsoleView
{
private:
    std::string input1;
    std::string input2:
public:
    UserInput(std::string input1, std::string input2);
    std::string UserInputLoop() const{return std::string;}
    ~UserInput();
};


#endif
