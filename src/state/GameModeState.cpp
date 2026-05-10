#include"state/GameModeState.hpp"
#include"state/StateManager.hpp"
#include"ResourceManager.hpp"
#include"state/GameState.hpp"

GameModeState::GameModeState(StateArguments& argState):IState(argState),
userVsUser("USER vs USER", argState.resourceManager.getFont("Roboto-Black.ttf"), argState.window.getSize(), [&]() {
	argState.stateManager.PushState(std::make_unique<GameState>(argState));
}),
userVsAi("USER vs AI", argState.resourceManager.getFont("Roboto-Black.ttf"), argState.window.getSize(), [&]() {
	argState.stateManager.PushState(std::make_unique<GameState>(argState, PlayerType::AI));
}),
ReturnMenu("RETURN", argState.resourceManager.getFont("Roboto-Black.ttf"), argState.window.getSize(), [&]() {
	argState.stateManager.PopState();
})
{
	auto sizedWindow = argState.window.getSize();

	userVsUser.setPosition(sf::Vector2f{
			sizedWindow.x*0.25f,
			sizedWindow.y*0.15f
		});

	userVsAi.setPosition(sf::Vector2f{
			sizedWindow.x*0.25f,
			sizedWindow.y*0.4f
		});

	ReturnMenu.setPosition(sf::Vector2f{
		 sizedWindow.x*0.25f,
		 sizedWindow.y*0.65f
		});

}

void GameModeState::HandleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		statArg.window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

		userVsUser.ReScale(event.size.width, event.size.height);
		userVsAi.ReScale(event.size.width, event.size.height);
		ReturnMenu.ReScale(event.size.width, event.size.height);

		userVsUser.setPosition(sf::Vector2f{
			event.size.width * 0.25f,
			event.size.height * 0.15f
			});

		userVsAi.setPosition(sf::Vector2f{
				event.size.width * 0.25f,
				event.size.height * 0.4f
			});

		ReturnMenu.setPosition(sf::Vector2f{
				event.size.width * 0.25f,
				event.size.height * 0.65f
			});

	}
	else if (event.type == sf::Event::MouseMoved) {
		auto pixelPos = sf::Mouse::getPosition(statArg.window);
		auto worldPos = statArg.window.mapPixelToCoords(pixelPos);
		userVsUser.handleMouseMove(worldPos);
		userVsAi.handleMouseMove(worldPos);
		ReturnMenu.handleMouseMove(worldPos);
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		auto pixelPos = sf::Mouse::getPosition(statArg.window);
		auto worldPos = statArg.window.mapPixelToCoords(pixelPos);
		userVsUser.handleMousePress(worldPos);
		userVsAi.handleMousePress(worldPos);
		ReturnMenu.handleMousePress(worldPos);
	}
}

void GameModeState::Update(sf::Time dt)
{
	

}

void GameModeState::DrawState()
{
	statArg.window.clear();
	statArg.window.draw(userVsUser);
	statArg.window.draw(userVsAi);
	statArg.window.draw(ReturnMenu);
	statArg.window.display();
}
