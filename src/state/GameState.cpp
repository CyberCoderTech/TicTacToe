#include"state/GameState.hpp"
#include"state/StateManager.hpp"
#include"ResourceManager.hpp"
#include"mvc/PlayerController.hpp"
#include"mvc/AIController.hpp"

GameState::GameState(StateArguments& argState,PlayerType typeUser):IState(argState),view(argState.window,argState.resourceManager.getFont("Roboto-Black.ttf"))
{
	if (typeUser == PlayerType::Human) {
		controller = std::make_unique<PlayerController>(view, model);
	}
	else if (typeUser == PlayerType::AI) {
		controller = std::make_unique<AIController>(view, model);
	}
}

void GameState::HandleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		statArg.stateManager.PopState();
	}
	else {
		controller->EventController(event);
	}
}

void GameState::Update(sf::Time dt)
{
}

void GameState::DrawState()
{
	view.draw(model.getBoard());
}
