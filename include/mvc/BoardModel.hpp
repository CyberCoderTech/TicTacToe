#pragma once

#include<array>
#include<span>
#include<variant>
#include<optional>

enum class CellState {
	None,
	X,
	O
};

enum class GameResult {
	WinX,
	WinO,
	Draw
};

class BoardModel {
public:
	BoardModel();
	~BoardModel() = default;

	void makeMove(int row, int col);

	void resetGame();

	std::variant<CellState, GameResult> getCurrentPlayer();

	std::span<const CellState> getBoard()const;


private:
	std::array<CellState, 9> mBoard;
	CellState currentPlayer;
	bool isFinishGame;

	std::optional<GameResult> currentGameResult();
	CellState getValue(int row, int col)const;

};