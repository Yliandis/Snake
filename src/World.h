#ifndef WORLD_H
#define WORLD_H

#include "Snake.h"

#include <cstdlib>
#include <ctime>

class World : public sf::Drawable
{
	public:
		
		World(sf::Vector2u, float);
		
		void processEvents();
		void update();
		sf::Time getUpdateTime() const;
		
	private:
		
		void resetFood();
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		
		sf::Vector2u m_size;
		float m_blockSize;
		
		sf::CircleShape m_food;
		sf::Vector2u m_foodPosition;
		
		sf::RectangleShape m_bounds [4];
		
		Snake m_snake;
};

#endif // WORLD_H
