
int UserInputLoop()
{
    std::vector<UMLClass> Classes;
    int count = 0;
    std::cout << "Enter the amount of Classes to add:" << std::endl;
    std::cin >> count;

    std::string ClassName, ClassAttribute;
    for(int i = 0; i < count; ++i)
    {
        std::cout << "Please enter the names of your classes: " << std::endl;

        std::cin >> ClassName;
        stf::cin >> ClassAttribute;

        Classes.set_class_name(ClassName);
        Classes.add_attribute(ClassAttribute);
    }

    for(const UMLClass & e : Classes)
    {
        std::cout << "UMLClass:" << std::endl;
        std::cout << e.getClassname() << " " << e.getAttributetname() << std::endl;
    }
}
