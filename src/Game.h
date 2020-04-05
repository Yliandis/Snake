#ifndef GAME_H
#define GAME_H

#include "Window.h"

class Game : private sf::NonCopyable
{
	public:
		
		Game();
		void run();
		
	private:
		
		void processEvents();
		void update();
		void render();
		
	private:
		
		Window m_window;
		
		sf::Clock m_clock;
		sf::Time m_elapsedTime;
		
	private:
		
		static const sf::Time UpdateTime;
};

#endif // GAME_H
