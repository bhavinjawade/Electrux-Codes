#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include "../include/funcs.h"

int main( int argc, char **argv )
{
	if( argc <= 1 ) {
		printf( "Usage: %s [Options] File(s)\n", argv[ 0 ] );
		exit( 0 );
	}
	
	struct String *sources;
	int source_count = get_sources( argc, ( const char ** )argv, &sources );
	
	if( source_count < 1) {
		printf( "Error: No source found in the arguments specified!\n" );
		exit( 0 );
	}
	
	int is_std_given = is_option_available( argc, ( const char ** )argv, "-std=" );
	
	int is_out_obj_given = is_option_available( argc, ( const char ** )argv, "-o" );
	
	bool is_src_cpp = is_source_cpp( source_count, sources );
	
	char fstr[800];
	
	if( is_src_cpp )
	{
		strcpy( fstr, "clang++ " );
		
		if( !is_std_given )
			strcat( fstr, "-std=c++14 " );
	}
	else
	{
		strcpy( fstr, "clang " );
		
		if( !is_std_given )
			strcat( fstr, "-std=c11 " );
	}
	
	for( int i = 1; i < argc; ++i )
	{
		strcat( fstr, argv[ i ] );
		strcat( fstr, " " );
	}
	
	if( !is_out_obj_given )
	{
		strcat( fstr, "-o ");
		strcat( fstr, get_output_file_name( sources ) );
	}
	
	printf( "%s\n", fstr );
	
	system( fstr );
	return 0;
}