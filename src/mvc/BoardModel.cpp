#include<algorithm>
#include "mvc/BoardModel.hpp"


BoardModel::BoardModel():currentPlayer(CellState::O),isFinishGame(false)
{
	mBoard.fill(CellState::None);
}

void BoardModel::makeMove(int row, int col)
{
	if (getValue(row,col) != CellState::None || isFinishGame) {
		return;
	}
	mBoard.at(row * 3 + col) = currentPlayer;
	currentPlayer = (currentPlayer == CellState::O) ? CellState::X : CellState::O;
	
}

void BoardModel::resetGame()
{
	mBoard.fill(CellState::None);
	isFinishGame = false;
	currentPlayer = CellState::O;
}


std::variant<CellState, GameResult> BoardModel::getCurrentPlayer() 
{
	if (auto valueGameResult = currentGameResult()) {
		isFinishGame = true;
		return *valueGameResult;
	}
	return currentPlayer;
}



std::span<const CellState> BoardModel::getBoard() const
{
	return mBoard;
}

std::optional<GameResult> BoardModel::currentGameResult()
{

	//Check Row [TODO] Check why row is column ?
	for (int row = 0; row < 3; row++) {
		if (getValue(0, row) != CellState::None &&
			getValue(0, row) == getValue(1, row) &&
			getValue(1, row) == getValue(2, row)) {
			return (currentPlayer == CellState::O) ? GameResult::WinX : GameResult::WinO;
		}
	}

	//Check Column
	for (int col = 0; col < 3; col++) {
		if (getValue(col,0) != CellState::None &&
			getValue(col,0) == getValue(col,1) &&
			getValue(col,1) == getValue(col,2)) {
			return (currentPlayer == CellState::O) ? GameResult::WinX : GameResult::WinO;
		}
	}

	//Check Cross
	if (getValue(0, 0) != CellState::None &&
		getValue(0, 0) == getValue(1, 1) &&
		getValue(1, 1) == getValue(2, 2)) {
		return (currentPlayer == CellState::O) ? GameResult::WinX : GameResult::WinO;
	}

	if (getValue(2, 0) != CellState::None &&
		getValue(2, 0) == getValue(1, 1) &&
		getValue(2, 0) == getValue(0, 2)) {
		return (currentPlayer == CellState::O) ? GameResult::WinX : GameResult::WinO;
	}

	//Check Draw
	if (std::all_of(std::begin(mBoard),
		std::end(mBoard),
		[](auto value) {
			return value != CellState::None;
		})) {
		return GameResult::Draw;
	}

	return std::nullopt;
}

CellState BoardModel::getValue(int row, int col)const
{
	return mBoard.at(row * 3 + col);
}
