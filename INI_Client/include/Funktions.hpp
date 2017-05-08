#pragma once



//Send packet to the user. Try max MAX_PACKET_TRIES times.
bool SendPacket(sf::TcpSocket &socket, sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
{
	int count = 0;

	while (count < max_tries)
	{
		if (socket.send(packet) == sf::Socket::Done)
			return true;

		++count;
	}

	return false;
}

//Receive packet from the user. Try max MAX_PACKET_TRIES times.
bool ReceivePacket(sf::TcpSocket &socket, sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
{
	packet.clear();

	int count = 0;

	while (count < max_tries)
	{
		if (socket.receive(packet) == sf::Socket::Done)
			return true;

		++count;
	}

	return false;
}
