#pragma once

#include<memory>

#include"IState.hpp"
#include"mvc/IBoardController.hpp"

enum class PlayerType {
	Human,
	AI
};

class GameState :public IState {
public:
	GameState(StateArguments& argState,PlayerType typeUser=PlayerType::Human);
	~GameState() = default;


	
	void HandleEvent(sf::Event& event) override;

	void Update(sf::Time dt) override;

	void DrawState() override;

private:
	BoardModel model;
	BoardView view;
	std::unique_ptr<IBoardController> controller;

};