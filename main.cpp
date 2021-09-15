#include <iostream>
#include <vector>
#include <string>
#include "UMLClass.h"
#include "UMLController.h"
#include "UMLModel.h"


int main()
{

    UMLModel model;
    UMLController controller {model};
    controller.execute();

    return 0;    
}

