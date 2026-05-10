#pragma once

#include"IBoardController.hpp"

class PlayerController:public IBoardController {
public:
	PlayerController(BoardView&, BoardModel&);
	virtual ~PlayerController() = default;

	void EventController(const sf::Event&)override;


};