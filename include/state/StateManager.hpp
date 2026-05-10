#pragma once

#include<stack>
#include<memory>
#include<optional>

#include"IState.hpp"

class StateManager
{
public:
	StateManager() = default;

	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;

	void PushState(std::unique_ptr<IState> state);
	void PopState();

	void Event(sf::Event& event);
	void Update(sf::Time dt);
	void Draw();

private:
	std::stack<std::unique_ptr<IState>> stackState;

	std::optional<std::reference_wrapper<IState>> GetCurrentState()const;

};

