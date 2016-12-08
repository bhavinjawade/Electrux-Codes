#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

std::vector<std::string> delimitfromargv(int argc, char **argv);

int main(int argc, char **argv)
{
	if(argc <= 2)
	{
		std::cout << "USAGE: " << argv[0] << " <c/cxx> <flags...> <file>\n";
		return 0;
	}

	std::vector<std::string> args = delimitfromargv(argc, argv);

	auto argsit = args.begin(); //Starting from the program name parameter
	++argsit; //Now at the type parameter

	std::string type = *argsit;
	++argsit; //Now at file (if 2 params) / flag(s) (if >= 3 params)

	std::string flags;
	std::string file;

	if(argc == 3)
	{
		std::string file = *argsit;
	}
	else
	{

		while(argsit != args.end())
		{
			if(argsit == args.end() - 1)
			{
				file = *argsit;
			}
			else
			{
				flags += (argsit == args.end() - 2) ? *argsit : ( *argsit + " " );
			}
			++argsit;
		}
	}
	
	std::string opfile; //Output file (source file minus extension)
	for(auto it = file.begin(); it != file.end(); ++it)
	{
		if( *it == '.' )
			break;
		opfile += *it;
	}
	
	std::string finale;
	if(type == "c" || type == "C")
	{
		finale = "gcc" + (flags.empty() ? " " : ( " " + flags + " ")) + "-o " + opfile + " " + file;
	}
	else
	{
		finale = "g++" + (flags.empty() ? " " : ( " " + flags + " ")) + "-o " + opfile + " " + file;
	}

	std::system(finale.c_str());

	return 0;
}

std::vector<std::string> delimitfromargv(int argc, char **argv)
{
	std::vector<std::string> delimstr;
	delimstr.clear();
	
	if(argc < 1) return delimstr;
	
	for(int i = 0; i < argc; ++i)
	{
		delimstr.push_back(argv[i]);
	}
	return delimstr;
}