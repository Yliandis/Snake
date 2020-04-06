#include "Game.h"

Game::Game()
: m_window (sf::VideoMode (800, 632), "Snake", sf::Style::Default)
, m_elapsedTime (sf::Time::Zero)
, m_world ({800u, 608u}, 16)
, m_isPaused (false)
{ }

void Game::run()
{
	m_clock.restart();
	
	while (m_window.isOpen())
	{
		processEvents();
		
		m_elapsedTime += m_clock.restart();
		while (m_elapsedTime > m_world.getUpdateTime())
		{
			m_elapsedTime -= m_world.getUpdateTime();
			if (!m_isPaused)
			{
				update();
			}
		}
		
		render();
	}
}

void Game::processEvents()
{
	handleWindowEvents();
	m_world.processEvents();
}

void Game::update()
{
	m_world.update();
}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_world);
	m_window.display();
}

void Game::handleWindowEvents()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				m_isPaused = !m_isPaused;
			}
		}
	}
}
