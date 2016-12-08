# All custom classes and functions for C/C++

Currently contains:

	C++
	
		Delimiter functions for C++ (CPP/Strings/delims.hpp)
	
			For use with the command line args.
		
				std::vector<std::string> delimitfromargv(int argc, char **argv);
		
			To cleave a string using a character as delimiter.
		
				std::vector<std::string> delimiter(std::string str, char delim);