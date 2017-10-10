#pragma once

class GameEngine
{
	sf::RenderWindow window;
	sf::Event event;

	Entities entities;
	
	uint32_t entityids;

	//Handles key release, called by pollevent.
	void handlekeyreleased()
	{
		//Handle escape key to close the window.
		if (event.key.code == sf::Keyboard::Escape) this->close();

		//TODO
	}

public:

	//Initialize the engine.
	void init(sf::VideoMode mode, std::string name, sf::Uint32 style)
	{
		//Initialize the window.
		window.create(mode, name, style);

		entityids = 0;
	}

	//Handle events.
	void pollevent()
	{
		//Handle all events in queue.
		while (window.pollEvent(event))
		{
			//Close the window if event received is of close.
			if (event.type == sf::Event::Closed) this->close();

			//If any key release is encountered, handle the key press.
			if (event.type == sf::Event::KeyReleased) this->handlekeyreleased();

			//Handle key presses.
			if (event.type == sf::Event::KeyPressed)
			{
				
			}
		}
	}
	
	//Creates an entity.
	uint32_t createentity()
	{
		assets.loadasset("skeleton_body", "Actors/walkcycle/BODY_skeleton");

		entities.addentity(entityids, assets.getasset("skeleton_body"));

		entities.setposition(entityids, sf::Vector2f(60, 50));

		entities.moveto(entityids, sf::Vector2f(60, 500));

		return entityids++;
	}

	//Update frame.
	void update()
	{
		entities.tick();
	}

	//check for Window::isopen();
	bool isopen()
	{
		return window.isOpen();
	}

	//Check for Window::close();
	bool close()
	{
		if (!window.isOpen()) return false;

		window.close();

		return true;
	}

	//Display the contents of window.
	void display()
	{
		window.display();
	}

	//Clear the window.
	void clear()
	{
		window.clear();
	}

	//TODO
	void draw()
	{
		window.draw(entities);
	}

	//Returns reference to the window.
	sf::RenderWindow & getwindow()
	{
		return this->window;
	}

};
