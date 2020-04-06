#include "Snake.h"


Snake::Snake(float blockSize)
: m_blockSize (blockSize)
{
	reset();
}

void Snake::tick()
{
	if (m_body.empty() || m_direction == Direction::None)
	{
		return;
	}
	
	move();
	checkCollisions();
}

void Snake::extend()
{
	if (m_body.empty() || m_direction == Direction::None)
	{
		return;
	}
	
	SnakeSegment newSegment = m_body.back();
	sf::Vector2u &newPosition = newSegment.position;
	
	if (m_body.size() == 1)
	{
		if (m_direction == Direction::Up)
		{
			++newPosition.y;
		}
		else if (m_direction == Direction::Down)
		{
			--newPosition.y;
		}
		else if (m_direction == Direction::Left)
		{
			++newPosition.x;
		}
		else // m_direction == Direction::Right
		{
			--newPosition.x;
		}
	}
	else
	{
		SnakeSegment &nextToTail = m_body[m_body.size() - 2];
		
		if (nextToTail.position.y < newPosition.y)
		{
			++newPosition.y;
		}
		else if (nextToTail.position.y > newPosition.y)
		{
			--newPosition.y;
		}
		else if (nextToTail.position.x < newPosition.x)
		{
			++newPosition.x;
		}
		else if (nextToTail.position.x > newPosition.x)
		{
			--newPosition.x;
		}
	}
	
	m_body.push_back(newSegment);
}

void Snake::speedUp()
{
	m_speed *= 1.08f;
}

/***********
 * Setters *
 **********/

void Snake::lose()
{
	m_isAlive = false;
	reset();
}

void Snake::setDirection(Direction direction)
{
	if (direction == Direction::Up && getPhysicalDirection() != Direction::Down)
	{
		m_direction = Direction::Up;
	}
	else if (direction == Direction::Down && getPhysicalDirection() != Direction::Up)
	{
		m_direction = Direction::Down;
	}
	else if (direction == Direction::Left && getPhysicalDirection() != Direction::Right)
	{
		m_direction = Direction::Left;
	}
	else if (direction == Direction::Right && getPhysicalDirection() != Direction::Left)
	{
		m_direction = Direction::Right;
	}
}

void Snake::increaseScore()
{
	++m_score;
}

/***********
 * Getters *
 **********/

sf::Vector2u Snake::getPosition() const
{
	if (m_body.empty())
	{
		return sf::Vector2u (1, 1);
	}
	else
	{
		return m_body.front().position;
	}
}

float Snake::getSpeed() const
{
	return m_speed;
}

unsigned Snake::getScore() const
{
	return m_score;
}

unsigned Snake::getLives() const
{
	return m_lives;
}

bool Snake::isAlive() const
{
	return m_isAlive;
}

/******************************
 * Special collision function *
 *****************************/

bool Snake::collides(sf::Vector2u position) const
{	
	for (const SnakeSegment& segment : m_body)
	{
		if (segment.position == position)
		{
			return true;
		}
	}
	
	return false;
}

/*******************
 * Private methods *
 ******************/

Direction Snake::getPhysicalDirection() const
{
	if (m_body.size() <= 1)
	{
		return m_direction;
	}
	else
	{
		const SnakeSegment &head = m_body[0];
		const SnakeSegment &neck = m_body[1];
		
		if (head.position.x < neck.position.x)
		{
			return Direction::Left;
		}
		else if (head.position.x > neck.position.x)
		{
			return Direction::Right;
		}
		else if (head.position.y < neck.position.y)
		{
			return Direction::Up;
		}
		else if (head.position.y > neck.position.y)
		{
			return Direction::Down;
		}
		else
		{
			return Direction::None;
		}
	}
}

void Snake::reset()
{
	m_body.clear();
	
	m_body.push_back({5u, 7u});
	m_body.push_back({5u, 6u});
	m_body.push_back({5u, 5u});
	
	m_direction = Direction::None;
	m_speed = 12.f;
	m_score = 0;
	m_lives = 3;
	m_isAlive = true;
}

void Snake::move()
{
	for (unsigned i = m_body.size() - 1 ; i > 0 ; --i)
	{
		m_body[i].position = m_body[i-1].position;
	}
	
	if (m_direction == Direction::Up)
	{
		--m_body[0].position.y;
	}
	else if (m_direction == Direction::Down)
	{
		++m_body[0].position.y;
	}
	else if (m_direction == Direction::Left)
	{
		--m_body[0].position.x;
	}
	else if (m_direction == Direction::Right)
	{
		++m_body[0].position.x;
	}
}

void Snake::checkCollisions()
{
	if (m_body.size() < 5)
	{
		return;
	}
	
	const SnakeSegment &head = m_body.front();
	
	for (unsigned i = 1 ; i < m_body.size() ; ++i)
	{
		if (head.position == m_body[i].position)
		{
			cut(m_body.size() - i);
			break;
		}
	}
}

void Snake::cut(unsigned segments)
{
	--m_lives;
	if (m_lives == 0)
	{
		m_isAlive = false;
	}
	
	for (unsigned i = 0 ; i < segments ; ++i)
	{
		m_body.pop_back();
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f (m_blockSize - 1, m_blockSize - 1));
	
	if (m_body.empty())
	{
		return;
	}
	
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(sf::Vector2f (m_body.front().position) * m_blockSize);
	target.draw(rectangle, states);
	
	rectangle.setFillColor(sf::Color::Blue);
	for (unsigned i = 1 ; i < m_body.size() ; ++i)
	{
		rectangle.setPosition(sf::Vector2f (m_body[i].position) * m_blockSize);
		target.draw(rectangle, states);
	}
}
