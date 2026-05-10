#include "mvc/PlayerController.hpp"


PlayerController::PlayerController(BoardView& argView, BoardModel& argModel):IBoardController(argView,argModel)
{
}

void PlayerController::EventController(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		
		sf::Vector2f mousePos = {
			static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y)
		};

		auto translateCordinate = mView.getBoardCoordinates(mousePos);

		mModel.makeMove(translateCordinate.x, translateCordinate.y);

		auto Player = mModel.getCurrentPlayer();
		mView.updateStatusDisplay(Player);

	}
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Space) {
		mModel.resetGame();
		auto Player = mModel.getCurrentPlayer();
		mView.updateStatusDisplay(Player);
	}
	else if (event.type == sf::Event::Resized) {
		float newWidth = static_cast<float>(event.size.width);
		float newHeight = static_cast<float>(event.size.height);

		mView.updateSize(newWidth, newHeight);

	}
}
