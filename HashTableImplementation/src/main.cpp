#include <iostream>
#include <string>
#include "../include/HashTable.hpp"

int main()
{
	Electrux::HashTable test( 10 );
	Electrux::HashKey key( "1" ),
						key2( "2" );

	std::cout << std::boolalpha
				<< test.Insert( key, "Hello") << "\t"
                << test.Insert( key2, "World!" ) << "\n";

	std::cout << test.Get( key ) << "\t" << test.Get( key2 ) << "\n";

	std::cout << key.GetTable() << "\t" << key2.GetTable() << "\n";


	return 0;
}