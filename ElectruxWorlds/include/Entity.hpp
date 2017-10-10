#pragma once


class Entity : public sf::Drawable
{
	uint32_t gid, uid;

	std::string name;

	sf::Sprite spr;

	sf::Vector2f newpos;

	bool isonfinalpos;

	float moveangle;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(spr);
	}

public:

	Entity()
	{
		isonfinalpos = true;
	}

	//Sets the entity group ID.
	void setgid(uint32_t id)
	{
		this->gid = id;
	}

	//Sets the entity unique ID.
	void setuid(uint32_t id)
	{
		this->uid = id;
	}

	//Gets the entity group ID.
	uint32_t getgid()
	{
		return this->gid;
	}

	//Gets the entity unique ID.
	uint32_t getuid()
	{
		return this->uid;
	}

	//Sets the entity name (optional).
	void setname(std::string name)
	{
		this->name = name;
	}

	//Gets the entity name.
	std::string getname()
	{
		return this->name;
	}

	//Load the texture.
	void loadtexture(sf::Texture &tex)
	{
		spr.setTexture(tex);
	}

	//Set the position of the sprite.
	void setposition(sf::Vector2f pos)
	{
		spr.setPosition(pos);
	}

	//Go to the given location.
	void moveto(sf::Vector2f pos)
	{
		//Set new position = the given pos.
		newpos = pos;

		//Set the is on final position boolean variable to b false.
		isonfinalpos = false;
		
		//Fetch the movement angle using atan2 function.
		moveangle = atan2(newpos.y - spr.getPosition().y, newpos.x - spr.getPosition().x);
	}

	//Update the object position and change it if the object is supposed to go to some position.
	void tick()
	{
		if (!isonfinalpos)
		{
			//Go to the new position based on SKIP (speed) and movement angle.
			spr.setPosition(spr.getPosition().x + SKIP * cos(moveangle), spr.getPosition().y + SKIP * sin(moveangle));
			
			//If the new position is in the bounds of the object, set the isonfinalpos variable to be true.
			if (this->isinbounds(newpos)) isonfinalpos = true;
		}
	}

	//Check if the position exists in bounds of object. Takes into account, the frame skips in movement.
	bool isinbounds(sf::Vector2f pos)
	{
		float skip = 0.75 * SKIP;

		float left = spr.getPosition().x - skip;
		float top = spr.getPosition().y - skip;

		float dist = 2 * skip;

		return left <= pos.x &&
				(left + dist) >= pos.x &&
				top <= pos.y &&
				(top + dist) >= pos.y;
	}

};