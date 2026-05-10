#include"state/MenuState.hpp"
#include"ResourceManager.hpp"
#include"state/StateManager.hpp"
#include"state/GameModeState.hpp"

MenuState::MenuState(StateArguments& argState):IState(argState),
exit("EXIT", argState.resourceManager.getFont("Roboto-Black.ttf"),argState.window.getSize(), [&]() {
	argState.window.close();
	}),
	runGame("START", argState.resourceManager.getFont("Roboto-Black.ttf"),argState.window.getSize(), [&]() {
	argState.stateManager.PushState(std::make_unique<GameModeState>(argState));
	})
{
	
	auto sizeWindow = argState.window.getSize();

	exit.setPosition(sf::Vector2f{
			sizeWindow.x * 0.25f,
			sizeWindow.y * 0.5f
		});

	runGame.setPosition(sf::Vector2f{
			sizeWindow.x * 0.25f,
			sizeWindow.y * 0.2f
		});

}

void MenuState::HandleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		statArg.window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

		exit.ReScale(event.size.width, event.size.height);
		runGame.ReScale(event.size.width, event.size.height);
		
		exit.setPosition(sf::Vector2f{
			event.size.width*0.25f,
			event.size.height*0.5f
			});

		runGame.setPosition(sf::Vector2f{
			event.size.width * 0.25f,
			event.size.height * 0.2f
			});

		
	}
	else if (event.type == sf::Event::MouseMoved) {
		auto pixelPos = sf::Mouse::getPosition(statArg.window);
		auto worldPos = statArg.window.mapPixelToCoords(pixelPos);
		runGame.handleMouseMove(worldPos);
		exit.handleMouseMove(worldPos);
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		auto pixelPos = sf::Mouse::getPosition(statArg.window);
		auto worldPos = statArg.window.mapPixelToCoords(pixelPos);
		runGame.handleMousePress(worldPos);
		exit.handleMousePress(worldPos);
	}
}

void MenuState::Update(sf::Time dt)
{
	
}

void MenuState::DrawState()
{
	statArg.window.clear();
	statArg.window.draw(exit);
	statArg.window.draw(runGame);
	statArg.window.display();
}
