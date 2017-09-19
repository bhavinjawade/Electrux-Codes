//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_DATA_HPP
#define PROJECTCREATOR_DATA_HPP

#include <map>
#include <string>

const std::map< std::string, std::string > LANGUAGES = {
	{ "c", "c" },
	{ "c++" , "cpp" }
};

const std::string CMAKE_MIN = "3.2";

class Flags
{
public:
	static const std::string LANG,
		DIR,
		PROJNAME,
		LIBS;
};

const std::string Flags::LANG     = "--lang";
const std::string Flags::DIR      = "--dir";
const std::string Flags::PROJNAME = "--name";
const std::string Flags::LIBS     = "--libs";

#endif //PROJECTCREATOR_DATA_HPP
