#pragma once

#include<SFML/Graphics.hpp>

class StateManager;
class ResourceManager;

struct StateArguments {
	sf::RenderWindow& window;
	StateManager& stateManager;
	ResourceManager& resourceManager;
};

class IState {
public:

	virtual ~IState() = default;
	virtual void HandleEvent(sf::Event& event) = 0;
	virtual void Update(sf::Time dt)=0;
	virtual void DrawState() = 0;

protected:
	IState(StateArguments& argState) :statArg{ argState } {

	}

	StateArguments& statArg;

};