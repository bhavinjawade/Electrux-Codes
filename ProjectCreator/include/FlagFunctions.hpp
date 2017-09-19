//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_FLAGFUNCTIONS_HPP
#define PROJECTCREATOR_FLAGFUNCTIONS_HPP

#include <iostream>
#include <vector>
#include "Data.hpp"

bool GetLangFromFlag( const std::vector< std::string > &args, std::string &language )
{
	auto langflag = std::find( args.begin(), args.end(), "--language" );

	// Language check.
	if( langflag == args.end() ) {
		std::cout << "Error: No language flag found. Use --language <lang> flag.\n";
		return false;
	}

	auto lang = langflag + 1;

	if( lang == args.end() || ( languages.find( *lang ) == languages.end() ) ) {
		std::cout << "Error: No (valid) language specified after the --language flag.\n";
		std::cout << "\tValid languages are:\n";

		for( auto lang : languages )
			std::cout << "\t\t" << lang.first << "\n";

		return false;
	}

	language = *lang;

	return true;
}

bool GetProjNameFromFlag( const std::vector< std::string > &args, std::string &proj )
{
	auto projnameflag = std::find( args.begin(), args.end(), "--name" );

	if( projnameflag == args.end() ) {
		std::cout << "Error: No Project Name flag found. Use --name <Project_Name> flag.\n";
		std::cout << "Note that no spaces are allowed in project name.\n";
		return false;
	}

	auto projname = projnameflag + 1;

	if( projname == args.end() || ( projname->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No project name specified after the --name flag.\n";
		return false;
	}

	proj = *projname;

	return true;
}

bool GetDirFromFlag( const std::vector< std::string > &args, std::string &dir )
{
	auto dirflag = std::find( args.begin(), args.end(), "--dir" );

	if( dirflag == args.end() ) {
		std::cout << "Note: Since no directory was specified, using current directory to create the project.\n";
		dir = ".";
		return false;
	}

	auto dirname = dirflag + 1;

	if( dirname == args.end() || ( dirname->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No directory specified after the --dir flag.\n";
		return false;
	}

	dir = *dirname;

	if( *dir.begin() != '/' && *dir.begin() != '.' )
		dir = "./" + dir;

	return true;
}

bool GetLibsFromFlag( const std::vector< std::string > &args, std::vector< std::string > &libs )
{
	auto libflag = std::find( args.begin(), args.end(), "--libs" );

	if( libflag == args.end() ) {
		std::cout << "Note: No library was specified.\n";
		return false;
	}

	auto dirs = libflag + 1;

	if( dirs == args.end() || ( dirs->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No directory specified after the --dir flag.\n";
		return false;
	}

	std::string temp;

	for( auto ch : *dirs ) {
		if( ch == ',' ) {
			libs.push_back( temp );
			temp.clear();
		} else {
			temp.push_back( ch );
		}
	}

	if( !temp.empty() )
		libs.push_back( temp );

	return true;
}

#endif //PROJECTCREATOR_FLAGFUNCTIONS_HPP
