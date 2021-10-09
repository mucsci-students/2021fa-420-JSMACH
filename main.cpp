
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/threads/pool.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "UMLClass.h"
#include "UMLController.h"
#include "UMLModel.h"
#include <nana/gui.hpp>

int main()
{
	using namespace nana;
	form fm;

	drawing{ fm }.draw([](paint::graphics& graph){
		graph.string({ 20, 20 }, "Click on the Window to Start ");
	});

	fm.show();


	//After the forum is clicked it will begin the user promt .
	fm.events().click([&fm]
	{
		inputbox::text ClassName("<bold red>ClassName</>", "Class Name");	//The format text is also available, the second parameter can be given for default value.
		inputbox::text Types("Types", std::vector<std::string>{ "Int", "Double", "Char", "String", "Float", "ObjType" }); // Store the options in a vector 
		inputbox::real Relationships("<bold blue>Relationships</>", 1, 1, 100, 1);
		inputbox::integer Methods("<bold green>Methods</>", 0, 0, 100, 1); //range of numbers you can pick are from 1-100 

		inputbox inbox(fm, "Please input <bold>your Class Methods</>.", "Class Methods");

		//Open the image file and load the inputbox template
		paint::image img("inputbox_images.bmp");

		//Setting up layout 
		inbox.image(img, true, { 380, 0, 40, 100 });
		inbox.image(img, false, { 420, 0, 40, 100 });
		inbox.image_v(img, true, { 0, 0, 380, 50 });
		inbox.image_v(img, false, { 0, 50, 380, 50 });

		//nana's way of checking user input is to use a verify function 
		inbox.verify([&ClassName](window handle)
		{
			if (ClassName.value().empty())
			{
				msgbox mb(handle, "Invalid input");
				mb << L"Class ClassName should not be empty, \n Please input your class ClassName.";
				mb.show();
				return false; //verification failed
			}
			return true; //verified successfully
		});

		//Call the show_modal() method to show the inputbox.
        //blocks the application execution until the inputbox gets closed.
		if (inbox.show_modal(ClassName, Types, Relationships, Methods))
		{
			auto n = ClassName.value();		//std::string in UTF-8
			auto t = Types.value();	//std::string in UTF-8
			auto r = Relationships.value();	//double
			auto m = Methods.value();		//int
		}
	});

	exec();
}