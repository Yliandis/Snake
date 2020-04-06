#include "World.h"

World::World(sf::Vector2u size, float blockSize)
: m_size (size)
, m_blockSize (blockSize)
, m_score (1, 20, 100, sf::Vector2f (0, size.y))
, m_bestScore (1, 20, 100, sf::Vector2f ((size.x - 100) / 2, size.y))
, m_lives (1, 20, 80, sf::Vector2f (size.x - 80, size.y))
, m_snake (blockSize)
{
	m_score.setBackgroundColor(sf::Color::Black);
	m_bestScore.setBackgroundColor(sf::Color::Black);
	m_lives.setBackgroundColor(sf::Color::Black);
	
	m_score.add("Score: 0");
	m_bestScore.add("Best: " + std::to_string(m_snake.getBestScore()));
	
	m_food.setFillColor(sf::Color::Red);
	m_food.setRadius(m_blockSize / 2);
	
	for (unsigned i = 0 ; i < 4 ; ++i)
	{
		m_bounds[i].setFillColor(sf::Color(255, 127, 0));
		
		if (i%2 == 1)
		{
			m_bounds[i].setSize(sf::Vector2f (m_size.x, m_blockSize));
		}
		else
		{
			m_bounds[i].setSize(sf::Vector2f (m_blockSize, m_size.y));
		}
		
		if (i < 2)
		{
			m_bounds[i].setPosition(0, 0);
		}
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f (m_size));
		}
	}
	
	srand(time(nullptr));
	resetFood();
}

void World::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_snake.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_snake.setDirection(Direction::Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_snake.setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_snake.setDirection(Direction::Down);
	}
}

void World::update()
{
	m_snake.tick();
	m_lives.add("Lives: " + std::to_string(m_snake.getLives()));
	
	sf::Vector2u position = m_snake.getPosition();
	
	if (position == m_foodPosition)
	{
		m_snake.extend();
		m_snake.increaseScore();
		m_score.add("Score: " + std::to_string(m_snake.getScore()));
		m_bestScore.add("Best: " + std::to_string(m_snake.getBestScore()));
		
		resetFood();
		
		if (m_snake.getScore() % 10 == 0)
		{
			m_snake.speedUp();
		}
	}
	
	if (m_snake.getLives() == 0 || position.x == 0 || position.y == 0 || position.x == m_size.x/unsigned(m_blockSize)-1 || position.y == m_size.y/unsigned(m_blockSize)-1)
	{
		m_snake.lose();
		m_score.add("Score: " + std::to_string(m_snake.getScore()));
	}
}

sf::Time World::getUpdateTime() const
{	
	return sf::seconds(1.f / m_snake.getSpeed());
}

void World::resetFood()
{
	unsigned maxX = m_size.x / unsigned(m_blockSize) - 2;
	unsigned maxY = m_size.y / unsigned(m_blockSize) - 2;
	
	do
	{
		m_foodPosition = {rand() % maxX + 1, rand() % maxY + 1};
	} while (m_snake.collides(m_foodPosition));
	
	m_food.setPosition(sf::Vector2f (m_foodPosition) * m_blockSize);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_food, states);
	
	for (unsigned i = 0 ; i < 4 ; ++i)
	{
		target.draw(m_bounds[i], states);
	}
	
	target.draw(m_score, states);
	target.draw(m_bestScore, states);
	target.draw(m_lives, states);
	
	target.draw(m_snake, states);
}
