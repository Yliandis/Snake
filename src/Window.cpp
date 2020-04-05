#include "Window.h"

/******************
 * Public methods *
 *****************/

Window::Window()
{
	setup({640u, 480u}, "Unnamed window");
}

Window::Window(sf::Vector2u size, const std::string& name)
{
	setup(size, name);
}

Window::~Window()
{
	destroy();
}

void Window::update()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_isOpen = false;
				break;
			
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::F5)
				{
					toggleFullscreen();
				}
				break;
			
			default:
				break;
		}
	}
}

void Window::draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::beginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	m_window.display();
}

/***********
 * Getters *
 **********/

sf::Vector2u Window::getSize() const
{
	return m_window.getSize();
}

bool Window::isOpen() const
{
	return m_isOpen;
}

/*******************
 * Private methods *
 ******************/

void Window::setup(sf::Vector2u size, const std::string& name)
{
	m_size = size;
	m_name = name;
	m_isOpen = true;
	m_isFullscreen = false;
	
	create();
}

void Window::create()
{
	sf::Uint32 style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Close;
	m_window.create(sf::VideoMode (m_size.x, m_size.y, 32), m_name, style);
}

void Window::destroy()
{
	m_window.close();
}

void Window::toggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}
