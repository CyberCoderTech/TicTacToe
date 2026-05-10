#pragma once

#include"IBoardController.hpp"

class AIController :
    public IBoardController
{
public:
    AIController(BoardView&, BoardModel&);
    virtual ~AIController() = default;

    void EventController(const sf::Event& event) override;

private:
    bool isBoardFull(std::span<const CellState> board)const;
    int evaluate(std::span<const CellState> board);
    int minmax(std::span<CellState> board, int depth, bool isMax);
    std::pair<int, int> findBestMove(std::span<CellState> board);
};

