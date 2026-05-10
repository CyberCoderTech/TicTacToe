#include "state/StateManager.hpp"

void StateManager::PushState(std::unique_ptr<IState> state)
{
	if (!state)return;
	stackState.push(std::move(state));

}

void StateManager::PopState()
{
	if (!stackState.empty()) {
		stackState.pop();
	}
}

void StateManager::Event(sf::Event& event)
{
	if (auto currState = GetCurrentState()) {
		currState->get().HandleEvent(event);
	}
}

void StateManager::Update(sf::Time dt)
{
	if (auto currState = GetCurrentState()) {
		currState->get().Update(dt);
	}
}

void StateManager::Draw()
{
	if (auto currState = GetCurrentState()) {
		currState->get().DrawState();
	}
}

std::optional<std::reference_wrapper<IState>> StateManager::GetCurrentState() const
{
	if (stackState.empty()) {
		return std::nullopt;
	}
	return *stackState.top();
}
