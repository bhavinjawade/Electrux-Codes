#include <iostream>
#include <cstdlib>
#include "INI_Parser.hpp"


int main()
{
	std::system("cls");

	Electrux::INI_Parser ini;
	/*
	ini.SetData("Test", "OneS", "One");
	ini.SetData("Test", "OneI", 1);
	ini.SetData("Test", "OneF", 1.0f);

	ini.SaveFile("Test.ini");
	*/

	ini.ParseFile("Test.ini");

	ini.DisplayAll();

	//ini.SetData("Test", "OneS", "Two"); //Modifies already existing data.

	//ini.DisplayAll();

	std::system("pause");
	return 0;
}