//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_HASHTABLE_HPP
#define HASHTABLEIMPLEMENTATION_HASHTABLE_HPP

#include <string>
#include "table.hpp"
#include "HashKey.hpp"

const int MAX_TABLES = 1000;

namespace Electrux
{
	class HashTable
	{
		int size;

		Table *tables[MAX_TABLES];

		int *lastlocfilled;

		int ctr;

	public:

		HashTable( int maxhashtablesize )
		{
			ctr = 0;

			size = maxhashtablesize;

			tables[ ctr ] = new Table( size );
			lastlocfilled = new int[size];

			for( int i = 0; i < size; ++i )
				lastlocfilled[ i ] = -1;
		}

		~HashTable()
		{
			for( int i = 0; i <= ctr; ++i )
				delete tables[ i ];

			delete[] lastlocfilled;
		}

		bool Insert( HashKey &key, std::string val )
		{
			int loc = this->Hash( key.GetKey());

			if( lastlocfilled[ loc ] == MAX_TABLES - 1 )
				return false;

			lastlocfilled[ loc ]++;

			if( lastlocfilled[ loc ] > ctr ) {
				tables[ lastlocfilled[ loc ]] = new Table( size );
				ctr++;
			}

			tables[ lastlocfilled[ loc ]]->Insert( loc, val );

			key.SetTable( lastlocfilled[ loc ] );

			return true;
		}

		std::string Get( const HashKey &key )
		{
			if( key.GetTable() < 0 ) return "";

			int loc = this->Hash( key.GetKey());

			return tables[ key.GetTable() ]->Get( loc );
		}

		int Hash( std::string key )
		{
			int temp = 0;

			for( auto ch : key )
				temp += ( int ) ch;

			return temp % size;
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_HASHTABLE_HPP
