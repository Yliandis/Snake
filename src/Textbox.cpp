#include "Textbox.h"

Textbox::Textbox()
{
	build();
	setup(3, 10, 150, {0.f, 0.f});
}

Textbox::Textbox(unsigned visible, unsigned charSize, unsigned width, sf::Vector2f position)
{
	build();
	setup(visible, charSize, width, position);
}

void Textbox::setup(unsigned visible, unsigned charSize, unsigned width, sf::Vector2f position)
{
	m_visible = visible;
	
	sf::Vector2f offset (2.f, 2.f);
	
	m_content.setString("");
	m_content.setCharacterSize(charSize);
	m_content.setPosition(position + offset);
	
	m_backdrop.setSize(sf::Vector2f (width, visible * (charSize * 1.2f)));
	m_backdrop.setPosition(position);
}

void Textbox::add(const std::string& message)
{
	m_messages.push_back(message);
	if (m_messages.size() > m_visible)
	{
		m_messages.erase(m_messages.begin());
	}
	
	updateRender();
}

void Textbox::clear()
{
	m_messages.clear();
	updateRender();
}

void Textbox::setBackgroundColor(sf::Color color)
{
	m_backdrop.setFillColor(color);
}

/*******************
 * Private methods *
 ******************/

void Textbox::build()
{
	if (!m_font.loadFromFile("media/fonts/arial.ttf"))
	{
		throw std::runtime_error ("Textbox::build() - Failed to load 'media/fonts/arial.ttf'");
	}
	m_content.setFont(m_font);
	m_content.setFillColor(sf::Color::White);
	
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
}

void Textbox::updateRender()
{
	std::string content;
	for (const std::string& message : m_messages)
	{
		content += message + "\n";
	}
	
	m_content.setString(content);
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_backdrop, states);
	target.draw(m_content, states);
}
