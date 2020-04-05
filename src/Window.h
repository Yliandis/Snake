#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

class Window : private sf::NonCopyable
{
	public:
		
		Window();
		Window(sf::Vector2u, const std::string&);
		~Window();
		
		void update();
		void draw(sf::Drawable&);
		
		void beginDraw();
		void endDraw();
		
		sf::Vector2u getSize() const;
		bool isOpen() const;
		
	private:
		
		void setup(sf::Vector2u, const std::string&);
		
		void create();
		void destroy();
		
		void toggleFullscreen();
		
	private:
		
		sf::RenderWindow m_window;
		
		sf::Vector2u m_size;
		std::string m_name;
		
		bool m_isOpen;
		bool m_isFullscreen;
};

#endif // WINDOW_H
