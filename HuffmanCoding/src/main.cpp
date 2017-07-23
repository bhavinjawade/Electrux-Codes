#include <iostream>
#include "../include/HuffmanCode.hpp"

// Algorithm driver.
int main(int argc, char *argv[])
{
	std::string test_str = "This is a test string";
	
	HuffmanCoding hcoding;
	
	hcoding.insert( test_str );
	
	hcoding.generate_huffman_coding();
	
	std::cout << "For statement: " << test_str << "\n";
	hcoding.display_huffman_codes();
	
	return 0;
}