#pragma once

#include<SFML/Graphics.hpp>
#include<functional>

class Button:public sf::Drawable,public sf::Transformable
{
public:
	Button() = default;
	Button(const std::string& label,sf::Font& font,const sf::Vector2u& winSize,std::function<void()> clickLogic);
	~Button() = default;

	void handleMouseMove(const sf::Vector2f& mousePosition);
	void handleMousePress(const sf::Vector2f& mousePosition);

	void ReScale(const int width, const int height);

private:

	enum class StateButton {
		Normal,
		Hovered,
		Pressed
	};

	StateButton m_state = StateButton::Normal;

	sf::RectangleShape outLineButton;
	sf::Text text;

	std::function<void()> onFunction;

	void updateVisualState();
	bool isHovered(const sf::Vector2f& mousePosition)const;

	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

