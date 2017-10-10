#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <INI_Parser.hpp>

//Includes Window.hpp
#include <SFML/Graphics.hpp>

//Includes System.hpp
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Custom Includes
#include "Data.hpp"
#include "AssetManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Texthandler.hpp"
#include "GameEngine.hpp"

//Load the SFML libraries.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")

int main()
{
	GameEngine engine;

	//font.loadFromFile(assetloc + "Fonts/Painter.ttf");

	engine.init(sf::VideoMode(1280,720), "Electrux Worlds", sf::Style::None);

	engine.createentity();

	while (engine.isopen())
	{
		engine.pollevent();
		engine.update();
		engine.clear();
		engine.draw();
		engine.display();
	}

	return 0;
}