#pragma once

#include"BoardModel.hpp"
#include"BoardView.hpp"

class IBoardController {
public:

	IBoardController(BoardView& view, BoardModel& model) :mView(view), mModel(model) {

	}

	virtual ~IBoardController() = default;

	virtual void EventController(const sf::Event& event) = 0;
protected:
	BoardView& mView;
	BoardModel& mModel;
};