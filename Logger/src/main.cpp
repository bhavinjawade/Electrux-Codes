#include <iostream>
#include "../include/Logger.hpp"

int main()
{
	Electrux::Logger log;

	log.setfile("testout.txt");
	log.logf("Testing %d, %f, %s, %c", 1, 2.3, "hello", 'c');
	
	return 0;
}
