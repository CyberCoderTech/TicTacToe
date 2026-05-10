#include"state/MenuState.hpp"
#include"state/StateManager.hpp"
#include"ResourceManager.hpp"

int main() {
	
	sf::RenderWindow window{ sf::VideoMode(800,400),"TicTacToc",sf::Style::Close };
	window.setFramerateLimit(60);

	StateManager manager;
	ResourceManager rsManager;

	StateArguments statsArguments{
		window,
		manager,
		rsManager
	};

	manager.PushState(std::make_unique<MenuState>(statsArguments));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			manager.Event(event);
		}

		manager.Update(sf::Time());

		manager.Draw();
	}

}