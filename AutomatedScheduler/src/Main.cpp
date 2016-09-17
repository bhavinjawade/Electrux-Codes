#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include <SFML\graphics.hpp>
#include "ExecProcess.hpp"
#include "SlicedTime.hpp"
#include "Data.hpp"
#include "JobHandler.hpp"
#include "TextHandler.hpp"
#include "Engine.hpp"
#include "PollEvent.hpp"

//Since I'm not using multibyte in execprocess string to wstring, it will fail if i put a multibyte char string for process

int main()
{
	system("cls");
	font.loadFromFile("arial.ttf");
	AutoSchedulerEngine Engine;
	Engine.Initialize(sf::VideoMode(800, 600), std::string("AutoScheduler"));
	Engine.SetFrameRate(60);
	int frame = 0;
	while (Engine.isRunning())
	{
		Engine.PollEvent();
		Engine.Clear();
		Engine.UpdateCount();
		if (frame == 60)
		{
			Engine.UpdateTimeAndExecute();
			frame = 0;

		}
		Engine.Draw();
		Engine.Display();
		++frame;
	}
	return 0;
}