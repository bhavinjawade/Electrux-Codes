#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct LogFiles
{
	std::string name; //File ID/Type
	std::fstream file;
};

class Logger
{
	std::vector<LogFiles *> logfiles;

public:

	bool OpenLog(std::string name, std::string filename)
	{
		logfiles.push_back(new LogFiles);
		(*(logfiles.end() - 1))->name = name;
		(*(logfiles.end() - 1))->file.open(filename, std::ios::app);

		if (!(*(logfiles.end() - 1))->file.is_open())
		{
			logfiles.erase((logfiles.end() - 1)); //TODO
			return false;
		}

		return true;
	}
};