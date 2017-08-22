#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

std::vector<std::string> delimitfromargv(int argc, char **argv);
void getnameextfromfile(std::string file, std::string &name, std::string &ext);

int main(int argc, char **argv)
{
	if(argc <= 1)
	{
		std::cout << "USAGE: " << argv[0] << " <flags...> <file>\n";
		return 0;
	}

	std::vector<std::string> args = delimitfromargv(argc, argv);

	auto argsit = args.begin(); //Starting from the program name parameter
	++argsit; //Now at file (if 2 params) / flag(s) (if >= 3 params)

	std::string type, flags, file;

	if(argc == 2)
	{
		file = *argsit;
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
	
	getnameextfromfile(file, opfile, type);
	
	std::string finale;
	if(type == "c" || type == "C")
	{
		finale = "clang" + (flags.empty() ? " " : ( " " + flags + " ")) + "-o " + opfile + " " + file;
	}
	else
	{
		finale = "clang++ -std=c++14" + (flags.empty() ? " " : ( " " + flags + " ")) + "-o " + opfile + " " + file;
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

void getnameextfromfile(std::string file, std::string &name, std::string &ext)
{
	std::string::iterator pos;

	name.clear();
	ext.clear();

	for(auto it = file.begin(); it != file.end(); ++it)
	{
		if( *it == '.' && it != file.end() - 1)
		{
			pos = it;
		}
	}

	for(auto it = file.begin(); it != pos; ++it)
	{
		name += *it;
	}

	for(pos = pos + 1; pos != file.end(); ++pos) //Increment first so that it dont count period.
	{
		ext += *pos;
	}
}
