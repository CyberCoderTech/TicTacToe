#pragma once

#include"IState.hpp"
#include"ui/Button.hpp"

class MenuState:public IState
{
public:
	MenuState(StateArguments& argState);
	~MenuState() = default;

	void HandleEvent(sf::Event& event)override;
	void Update(sf::Time dt) override;
	void DrawState() override;

private:
	Button exit, runGame;
};

