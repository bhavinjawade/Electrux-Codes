# Compile C/C++ code using a single program/command.

Compile C/C++ code using a command:

Assuming the executable name of the compiled code is generator,
	
	Prompt> generator <c/c++> <flags...> <source file>
		
	Example:
	
		C Code:
		
		Prompt> generator c -pthread -lm test.c
		
		C++ Code:
		
		Prompt> generator c++ -std=c++11 test.c


Note that number of flags is not set. But the program will take the
LAST parameter as the source file ALWAYS.

Also, the program will generate the executable (-o <file>) automatically
as per the name of source file (source file minus the extension).

Requisites:

C++ 11 is REQUIRED for the auto keyword (Use compiler option -std=c++11 on g++).