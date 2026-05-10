#include "ui/Button.hpp"


Button::Button(const std::string& label, sf::Font& font,const sf::Vector2u& winSize, std::function<void()> clickLogic):onFunction{clickLogic}
{
	outLineButton.setFillColor(sf::Color::Red);
	outLineButton.setPosition(sf::Vector2f{ 0,0 });
	outLineButton.setSize(sf::Vector2f{
			static_cast<float>(winSize.x*0.5f),
			static_cast<float>(winSize.y*0.2f)
		});

	text.setFont(font);
	text.setCharacterSize(static_cast<float>(winSize.y*0.15f));
	text.setString(label);

	auto textBounds = text.getLocalBounds();

	text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		           textBounds.top + textBounds.height/2.0f);

	auto buttonPosition = outLineButton.getPosition();
	auto buttonSize = outLineButton.getSize();

	text.setPosition(
		buttonPosition.x+buttonSize.x/2.0f,
		buttonPosition.y+buttonSize.y/2.0f
	);
}

void Button::handleMouseMove(const sf::Vector2f& mousePosition)
{
	m_state = isHovered(mousePosition) ? StateButton::Hovered : StateButton::Normal;
	updateVisualState();
}

void Button::handleMousePress(const sf::Vector2f& mousePosition)
{
	if (isHovered(mousePosition) && onFunction) {
		onFunction();
	}
}





void Button::ReScale(const int width, const int height)
{
	outLineButton.setSize(sf::Vector2f{
		width * 0.5f,
		height * 0.2f
		});


	text.setCharacterSize(static_cast<float>(height * 0.15f));

	auto textBounds = text.getLocalBounds();

	auto buttonPosition = outLineButton.getPosition();
	auto buttonSize = outLineButton.getSize();

	if (textBounds.width >= buttonSize.x) {
		text.setCharacterSize(static_cast<float>(height * 0.10f));
		textBounds = text.getLocalBounds();
	}
	
	text.setOrigin(
		textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f
	);

	text.setPosition(
		buttonPosition.x + buttonSize.x / 2.f,
		buttonPosition.y + buttonSize.y / 2.f
	);

}


void Button::updateVisualState()
{
	switch (m_state) {
	case StateButton::Normal: {
		outLineButton.setFillColor(sf::Color::Red);
	}break;
	case StateButton::Hovered: {
		outLineButton.setFillColor(sf::Color::Green);
	}break;
	case StateButton::Pressed: {
		outLineButton.setFillColor(sf::Color::Blue);
	}break;
	}
}

bool Button::isHovered(const sf::Vector2f& mousePosition) const
{
	sf::Transform combined = getTransform() * outLineButton.getTransform(); 
	sf::FloatRect localBounds = outLineButton.getLocalBounds(); 
	sf::FloatRect globalBounds = combined.transformRect(localBounds); 
	return globalBounds.contains(mousePosition);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	states.transform *= getTransform();
	target.draw(outLineButton,states);
	target.draw(text,states);
	
}
