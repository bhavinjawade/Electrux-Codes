//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_HASHKEY_HPP
#define HASHTABLEIMPLEMENTATION_HASHKEY_HPP

#include <string>
#include "Consts.hpp"
#include "TemplateDefs.hpp"

namespace Electrux
{

	template < typename T >
	class HashKey
	{
		int table;
		T key;

		void GenHash()
		{
			hashval = GetHash( key ) % TABLE_SIZE;
		}

	public:

		int hashval;

		HashKey()
		{
			table = -1;
		}

		HashKey( T key )
		{
			table = -1;
			this->key = key;
			this->GenHash();
		}

		T GetKey() const
		{
			return key;
		}

		int GetTable() const
		{
			return table;
		}

		int operator ()() const
		{
			return hashval;
		}

		void SetKey( T key )
		{
			this->key = key;
			this->GenHash();
		}

		void SetTable( int table )
		{
			this->table = table;
		}

		void operator =( T key )
		{
			this->table = -1;
			this->key = key;
			this->GenHash();
		}
	};
}

#endif //HASHTABLEIMPLEMENTATION_HASHKEY_HPP
