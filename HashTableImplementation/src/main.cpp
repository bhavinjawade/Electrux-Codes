#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "../include/HashTable.hpp"

const int MAX_STR_COUNT = 1000000;

int main()
{

	std::fstream file( "../src/words.txt", std::ios::in );

	std::string *line;
	line = new std::string[ MAX_STR_COUNT ];

	int ctr = 0;

	while( std::getline( file, line[ ctr ] ) && ctr < MAX_STR_COUNT )
		ctr++;

	for( int i = 1; i <= 100; ++i ) {

		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

		Electrux::HashTable< std::string, std::string > test;
		Electrux::HashKey< std::string > *keys;
		keys = new Electrux::HashKey< std::string >[ MAX_STR_COUNT / 2 ];

		int currmax = i * 10000;

		for( int j = 0; j < currmax; j += 2 )
			keys[ j / 2 ] = line[ j ];


		for( int j = 0; j < currmax; j += 2 )
			test.Insert( keys[ j / 2 ], line[ (j + 1)/2 ] );

		//for( int i = 0; i < currmax / 2; ++i )
		//	test.Get( keys[ i ] );

		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>( end - start );

		std::cout << "Table Count: " << test.GetCtr() << "\tPair Count: " << test.GetCount() << "\tTime taken: " << diff.count() << "ms" << "\n";
	}

	return 0;
}