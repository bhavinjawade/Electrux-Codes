#pragma once


class User : public sf::TcpSocket
{
	std::string name;

	std::string dbconnect;

public:

	User()
	{
		dbconnect.clear();
	}

	void SetName(std::string name)
	{
		this->name = name;
	}

	std::string GetName()
	{
		return this->name;
	}

	bool IsDBConnected()
	{
		return !dbconnect.empty();
	}

	std::string GetDBConnected()
	{
		return dbconnect;
	}

	void SetDBConnected(std::string db)
	{
		dbconnect = db;
	}

};