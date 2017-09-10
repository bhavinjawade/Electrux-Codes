//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_HASHKEY_HPP
#define HASHTABLEIMPLEMENTATION_HASHKEY_HPP

#include <string>

namespace Electrux
{
	class HashKey
	{
		int table;
		std::string key;

	public:

		HashKey()
		{
			table = -1;
		}

		HashKey( std::string key )
		{
			table = -1;
			this->key = key;
		}

		std::string GetKey() const
		{
			return key;
		}

		int GetTable() const
		{
			return table;
		}

		void SetKey( std::string key )
		{
			this->key = key;
		}

		void SetTable( int table )
		{
			this->table = table;
		}

		void operator =( std::string key )
		{
			this->table = -1;
			this->key = key;
		}
	};
}

#endif //HASHTABLEIMPLEMENTATION_HASHKEY_HPP
