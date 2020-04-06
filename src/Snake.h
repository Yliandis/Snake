#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <fstream>
#include <stdexcept>

struct SnakeSegment
{
	SnakeSegment(unsigned x, unsigned y)
	: position (x, y)
	{ }
	
	sf::Vector2u position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Snake : public sf::Drawable
{
	public:
		
		Snake(float blockSize);
		~Snake();
		
		void reset();
		
		void tick();
		
		void extend();
		void speedUp();
		
		void lose();
		void setDirection(Direction);
		void increaseScore();
		void decreaseLife();
		
		sf::Vector2u getPosition() const;
		float getSpeed() const;
		unsigned getScore() const;
		unsigned getBestScore() const;
		unsigned getLives() const;
		bool isAlive() const;
		
		bool collides(sf::Vector2u) const;
		
		void cancel();
		void autoRotate(unsigned, unsigned);
		
	private:
		
		Direction getPhysicalDirection() const;
		
		void move();
		void checkCollisions();
		void cut(unsigned);
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
		void loadBestScore();
		void saveBestScore() const;
		
	private:
		
		SnakeContainer m_body;
		
		float m_blockSize;
		
		Direction m_direction;
		float m_speed;
		unsigned m_score;
		unsigned m_bestScore;
		unsigned m_lives;
		bool m_isAlive;
};

#endif // SNAKE_H
