#include "Game.h"

#include <iostream>

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}
	
	return 0;
}
