#pragma once

#include"IState.hpp"
#include"ui/Button.hpp"

class GameModeState : public IState {
public:

	GameModeState(StateArguments& argState);

	~GameModeState() = default;

	void HandleEvent(sf::Event& event) override;

	void Update(sf::Time dt) override;

	void DrawState() override;

private:
	Button userVsUser, userVsAi, ReturnMenu;
};