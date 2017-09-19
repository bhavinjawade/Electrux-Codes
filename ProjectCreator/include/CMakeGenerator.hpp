//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_CMAKEGENERATOR_HPP
#define PROJECTCREATOR_CMAKEGENERATOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "FindSFML.hpp"
#include "DirFileFunctions.hpp"

std::string GetSFMLCMake( std::string &project, std::string &cmakemodfolder );

void GenCMakeConfig( std::string &project, std::string &projfolder, std::string &lang, std::vector< std::string > &libs )
{
	std::string srcfile = "main." + languages.find( lang )->second;
	std::string cmakestr =
		std::string("cmake_minimum_required(VERSION 3.2)\n") +
			"project(" + project + ")\n" +
			"\n" +
			"set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++14\")\n" +
			"\n" +
			"set(SOURCE_FILES src/" + srcfile + ")\n" +
			"add_executable(" + project + " ${SOURCE_FILES})\n" +
			"\n" +
			"set(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_LIST_DIR}/cmake_modules\")\n";

	std::string cmakemodfolder = projfolder + "/cmake_modules";
	CreateDir( cmakemodfolder );

	if( std::find( libs.begin(), libs.end(), "sfml" ) != libs.end() )
		cmakestr += GetSFMLCMake( project, cmakemodfolder );


	CreateFileWithContents( projfolder + "/CMakeLists.txt", cmakestr );
}


std::string GetSFMLCMake( std::string &project, std::string &cmakemodfolder )
{
	std::string sfmlstr =
		std::string("find_package(SFML REQUIRED system window graphics network audio)\n") +
		"if (SFML_FOUND)\n" +
		"    include_directories(${SFML_INCLUDE_DIR})\n" +
		"    target_link_libraries(" + project + " ${SFML_LIBRARIES})\n" +
		"endif()";

	CreateFileWithContents( cmakemodfolder + "/FindSFML.cmake", findsfml );

	return sfmlstr;
}

#endif //PROJECTCREATOR_CMAKEGENERATOR_HPP
