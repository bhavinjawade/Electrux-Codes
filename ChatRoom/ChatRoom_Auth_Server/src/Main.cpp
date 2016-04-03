#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <list>
#include <functional>
#include <sqlite3.h>
#include <fstream>
#include <thread>
#include <mutex>
#include "Enums.hpp"
#include "Data.hpp"
#include "Users.hpp"
#include "Database.hpp"
#include "Functions.hpp"
#include "Remover.hpp"

int main()
{
	res = udb.Open();
	if (res != SQLITE_OK)
	{
		std::cout << "ERROR! " << std::endl;
		std::cout << "Could not open DataBase! Exiting!!";
		udb.Close();
		return 0;
	}
	udb.CheckDB();
	udb.SetAllOffline();
	sf::TcpListener listener;
	listener.listen(8080);
	sf::SocketSelector selector;
	selector.add(listener);
	sf::Packet packet;
	RemoveHandler remover;
	std::vector<std::thread> threads;
	std::cout << "\nAuthentication server ready to accept connections.";
	while (true)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener))
			{
				Users* client = new Users;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					selector.add(*client);
					packet.clear();
					threads.push_back(std::thread(AddClientToList, client));
				}
				else
				{
					delete client;
				}
			}
			else
			{
				for (std::list<Users*>::iterator receivefrom = clients.begin(); receivefrom != clients.end(); ++receivefrom)
				{
					Users& client = **receivefrom;
					if (selector.isReady(client))
					{
						packet.clear();
						if (client.receive(packet) == sf::Socket::Disconnected)
						{
							remover.AddToRemove(&client);
							selector.remove(client);
							continue;
						}
					}
				}
			}
		}
		remover.UpdateList();
	}
	for (auto it = threads.begin(); it != threads.end(); ++it)
	{
		it->join();
	}
	return 0;
}