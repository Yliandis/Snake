#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <stdexcept>

using MessageContainer = std::vector<std::string>;

class Textbox : public sf::Drawable
{
	public:
		
		Textbox();
		Textbox(unsigned visible, unsigned charSize, unsigned width, sf::Vector2f position);
		
		void setup(unsigned visible, unsigned charSize, unsigned width, sf::Vector2f position);
		
		void add(const std::string&);
		void clear();
		
		void setBackgroundColor(sf::Color);
		
	private:
		
		void build();
		void updateRender();
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		
		MessageContainer m_messages;
		unsigned m_visible;
		
		sf::RectangleShape m_backdrop;
		sf::Font m_font;
		sf::Text m_content;
};

#endif // TEXTBOX_H
