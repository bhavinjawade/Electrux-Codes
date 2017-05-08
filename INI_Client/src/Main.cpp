#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Enums.hpp"
#include "Data.hpp"
#include "Funktions.hpp"
#include "InitNetwork.hpp"


//Load the SFML network and system libraries.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-network-d.lib")

int main()
{

	sf::TcpSocket socket;

	if (!InitNetwork(socket))
	{
		std::cout << "Error in network. Please try restarting.\n";
		std::system("pause");
		return 0;
	}

	std::system("pause");
	return 0;
}