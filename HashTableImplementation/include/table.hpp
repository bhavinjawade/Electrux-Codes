//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_TABLE_HPP
#define HASHTABLEIMPLEMENTATION_TABLE_HPP

#include <string>

namespace Electrux
{
	class Table
	{
		// Array of strings which are to be stored.
		std::string *data;
		int size;
		bool *filledloc;

	public:

		Table( int datasize )
		{
			size = datasize;
			data = new std::string[datasize];
			filledloc = new bool[datasize];
		}

		~Table()
		{
			delete[] data;
			delete[] filledloc;
		}

		bool Insert( int loc, std::string data )
		{
			if( loc >= size ) return false;

			if( filledloc[ loc ] ) return false;

			this->data[ loc ] = data;
			filledloc[ loc ] = true;

			return true;
		}

		bool Delete( int loc )
		{
			if( loc >= size ) return false;
			if( !filledloc[ loc ] ) return false;

			data[ loc ].clear();
			filledloc[ loc ] = false;

			return true;
		}

		std::string Get( int loc )
		{
			return (loc >= size) ? "" : data[ loc ];
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_TABLE_HPP
