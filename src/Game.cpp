#include "Game.h"

const sf::Time Game::UpdateTime = sf::seconds(1.f / 60.f); // 60 FPS

Game::Game()
: m_window ({800u, 600u}, "Snake")
, m_elapsedTime (sf::Time::Zero)
{ }

void Game::run()
{
	m_clock.restart();
	
	while (m_window.isOpen())
	{
		processEvents();
		
		m_elapsedTime += m_clock.restart();
		while (m_elapsedTime > UpdateTime)
		{
			m_elapsedTime -= UpdateTime;
			update();
		}
		
		render();
	}
}

void Game::processEvents()
{ }

void Game::update()
{
	m_window.update();
	// then update with UpdateTime
}

void Game::render()
{
	m_window.beginDraw();
	m_window.endDraw();
}
