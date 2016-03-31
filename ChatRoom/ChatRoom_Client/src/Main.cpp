#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <sstream>
#include "Data.hpp"
#include "Enums.hpp"
#include "TextHandler.hpp"
#include "Connector.hpp"
#include "Engine.hpp"
#include "PollEvent.hpp"
#include "InitNetwork.hpp"

std::string windowname = "Chat Room";

int main()
{
	font.loadFromFile("Assets/Fonts/BOOKOS.TTF");
	ChatEngine Engine;
	if (!Engine.IsConnected())
	{
		system("pause");
		return 0;
	}
	Engine.Init(sf::VideoMode(800, 600), windowname);

	while (Engine.IsOpen())
	{
		Engine.PollEvent();
		Engine.Clear();
		Engine.Update();
		Engine.Draw();
		Engine.Display();
	}
	return 0;
}