#pragma once

class Entities : public sf::Drawable
{
	std::map<uint32_t, Entity *> entities;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (auto entity : entities)
			target.draw(*entity.second);
	}

public:

	~Entities()
	{
		for (auto entity : entities)
		{
			delete entity.second;
		}
	}

	bool addentity(uint32_t id, sf::Texture &tex)
	{
		if (entities.find(id) != entities.end()) return false;

		entities[id] = new Entity;

		entities[id]->loadtexture(tex);

		return true;
	}

	bool setposition(uint32_t id, sf::Vector2f pos)
	{
		if (entities.find(id) == entities.end()) return false;

		entities[id]->setposition(pos);

		return true;
	}

	bool deleteentity(uint32_t id)
	{
		if (entities.find(id) == entities.end()) return false;

		delete entities[id];

		entities.erase(id);

		return true;
	}

	Entity * getentity(uint32_t id)
	{
		return entities.find(id) == entities.end() ? nullptr : entities[id];
	}
	
	bool moveto(uint32_t id, sf::Vector2f newpos)
	{
		if (entities.find(id) == entities.end()) return false;
		
		entities[id]->moveto(newpos);

		return true;
	}

	void tick()
	{
		for (auto entity : entities)
		{
			entity.second->tick();
		}
	}

};