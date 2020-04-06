#ifndef GAME_H
#define GAME_H

#include "World.h"

class Game : private sf::NonCopyable
{
	public:
		
		Game();
		void run();
		
	private:
		
		void processEvents();
		void update();
		void render();
		
		void handleWindowEvents();
		
	private:
		
		sf::RenderWindow m_window;
		
		sf::Clock m_clock;
		sf::Time m_elapsedTime;
		
		World m_world;
};

#endif // GAME_H
