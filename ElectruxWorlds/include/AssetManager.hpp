#pragma once

class AssetManager
{
	std::map<std::string, sf::Texture> assets;

	uint32_t width, height;

public:

	//Width = 32 and height = 32 of default asset when an asset isnt found.
	AssetManager()
	{
		width = height = 32;
	}

	//Width and height of default asset when an asset isnt found.
	AssetManager(uint32_t size)
	{
		this->width = size;
		this->height = size;

		sf::Texture tex;
		
		tex.create(this->width, this->height);

		assets["NotFound"] = tex;
	}

	//Load the given texture by the given texturename.
	bool loadasset(std::string name, std::string textname)
	{
		sf::Texture tex;
		
		if (assets.find(name) != assets.end()) return false;

		if (!tex.loadFromFile(assetloc + textname + assetext)) return false;

		assets[name] = tex;
		
		return true;
	}

	//Unload the given asset.
	bool unloadasset(std::string textname)
	{
		if (assets.find(textname) == assets.end()) return false;

		assets.erase(textname);

		return true;
	}

	//Get the reference to given asset.
	sf::Texture & getasset(std::string textname)
	{
		if (assets.find(textname) == assets.end()) return assets["NotFound"];

		return assets[textname];
	}

} assets(assetsize);