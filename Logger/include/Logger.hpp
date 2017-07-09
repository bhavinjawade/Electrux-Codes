#include <iostream>
#include <cstdarg>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace Electrux
{
	class Logger
	{
		std::string filestr;
		std::fstream file;

		std::string errorstring;

		bool logtofile, logtoconsole;

		// Returns the current time in the form of std::string.
		std::string getcurrenttime()
		{
			// Get current time, and convert it into time_t object.
			auto now = std::chrono::system_clock::now();
			auto timenow = std::chrono::system_clock::to_time_t(now);

			// Create a string stream object to put the formatted time into.
			std::stringstream currtime;
			currtime << std::put_time(std::localtime(&timenow), "%Y-%m-%d %X");

			// Return the string stream object data as an std::string.
			return currtime.str();
		} 

		public:

		// Constructor for the object.
		Logger()
		{
			logtofile = false;
			logtoconsole = true;
		}

		// Destructor for the object.
		~Logger()
		{
			// Close file if one is opened.
			if(file.is_open()) file.close();
		}

		// Actually logs the data on the console and/or file along with the current time stamp.
		void log(std::string str)
		{
			// Create a new string object.
			std::string fstr;

			// Add the current time stamp to the final string to be logged.
			fstr = "[";
			fstr += this->getcurrenttime();
			fstr += "] : ";
			fstr += str;

			// If the log to file flag is true, log the string to file if it is opened.
			if(logtofile)
				if(file.is_open()) file << fstr << "\n";

			// If the log to console flag is true, log the string to console.
			if(logtoconsole)
				std::cout << fstr << "\n";
		}

		// Log as a formatted string.
		void logf(char const *str, ...)
		{
			// Initialize the argument list as args.
			std::va_list args;
			va_start(args, str);

			// A string object to store the end string.
			std::string finalstr;

			// While the given char * has some data in it.
			while(*str != '\0')
			{
				// Check if the current character in str is a modulo operator (%).
				if(*str == '%')
				{
					// Increment the pointer to the next character.
					++str;

					// If the current character is d/i, replace this part with the next int from arg list.
					if(*str == 'd' || *str == 'i')
					finalstr += std::to_string(va_arg(args, int));

					// If it is s, replace this part with the next char * from the arg list.
					else if(*str == 's')
					finalstr += va_arg(args, char *);

					// If it is f, replace this part with the next float from the arg list.
					// Note that the parameter is actually double because va_arg wont take float.
					else if(*str == 'f')
					finalstr += std::to_string((float)va_arg(args, double));

					// If it is c, replace this part with the next character from the arg list.
					// Note that the parameter is actually int because va_arg takes characters as int.
					else if(*str == 'c')
					finalstr += (char)va_arg(args, int);

					// If it is %, we simply need a % operator to be displayed.
					else if(*str == '%')
					finalstr += '%';

					// Increment the pointer to the next character and keep going on.
					++str;
				}

				// The finalstr object must be filled with the characters of the str pointer.
				finalstr += *str;
				++str;
			}

			// End the va_list.
			va_end(args);

			// Call the log function with the formatted string object.
			this->log(finalstr);
		}

		// Set console logging flag.
		void setlogtoconsole(bool val) { logtoconsole = val; }

		// Set file logging flag.
		void setlogtofile(bool val) { logtofile = val; }

		// Get value of the logtoconsole flag.
		bool getlogtoconsole() { return logtoconsole; }

		// Get value of the logtofile flag.
		bool getlogtofile() { return logtofile; }

		// Set the file string and open the said file.
		bool setfile(std::string filename)
		{
			// Close the former file if one is open.
			this->closefile();

			// Set the current filename to the given filename and open it in append mode.
			filestr = filename;
			file.open(filestr, std::ios::app);

			// Set file logging flag to true.
			logtofile = true;

			// Return the status of file (if it is opened successfully or not).
			return file.is_open();
		}

		// Close the current file being used.
		void closefile()
		{
			// Set file logging flag to false.
			logtofile = false;

			// If the file object has a file open, close it. 
			if(file.is_open())
			file.close();

			// Clear the file string object.
			filestr.clear();
		}

		// Get the name of the file used to log.
		std::string getfile() { return filestr; }
	};
}
