#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include "../include/ToVector.hpp"
#include "../include/Data.hpp"
#include "../include/FlagFunctions.hpp"
#include "../include/CMakeGenerator.hpp"
#include "../include/DirFileFunctions.hpp"

int main( int argc, const char **argv )
{
	if( argc < 2 ) {
		std::cout << "Syntax: " << argv[ 0 ] << " --<flag> <value> ...\n";
		return 0;
	}


	auto args = ConvertToVector( argc, argv );

	std::string language, projectname, dirname;

	// If there is no language specified, or no project name given, exit.
	if( !GetLangFromFlag( args, language )  || !GetProjNameFromFlag( args, projectname ) )
		return 0;


	std::cout << "Generating project " << projectname << "...\n\n";



	// Get extension of language.
	auto extension = LANGUAGES.find( language )->second;

	// Get directory, if specified, from command line.
	GetDirFromFlag( args, dirname );

	// Create the actual folder for the project.
	std::string projfolder,
			srcfolder,
			includefolder,
			buildfolder;

	SetFolderPaths( dirname, projectname, projfolder, srcfolder, includefolder, buildfolder );

	CreateDir( projfolder );

	CreateDir( srcfolder );
	CreateDir( includefolder );
	CreateDir( buildfolder );


	CreateFileWithContents( srcfolder + "/main." + extension );

	std::vector< std::string > libs;
	if( GetLibsFromFlag( args, libs ) )
		GenCMakeConfig( projectname, projfolder, language, libs );



	std::cout << "\nGeneration finished!\n";

	return 0;
}
