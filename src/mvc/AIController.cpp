#include "mvc/AIController.hpp"

#include<iostream>

AIController::AIController(BoardView& argView, BoardModel& argModel):IBoardController(argView,argModel)
{

}

void AIController::EventController(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		sf::Vector2f mousePos = {
			static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y)
		};

		auto translateCordinate = mView.getBoardCoordinates(mousePos);

		mModel.makeMove(translateCordinate.x, translateCordinate.y);


		auto Player = mModel.getCurrentPlayer();
		mView.updateStatusDisplay(Player);

		if (auto value = std::get_if<CellState>(&Player)) {
			if (*value == CellState::X) {
				std::array<CellState, 9> tmpBoard;
				auto modelBoard = mModel.getBoard();
				std::copy(std::begin(modelBoard), std::end(modelBoard), std::begin(tmpBoard));

				auto bestMoveAI = findBestMove(tmpBoard);

				mModel.makeMove(bestMoveAI.first, bestMoveAI.second);
				auto Player = mModel.getCurrentPlayer();
				mView.updateStatusDisplay(Player);
			}
		}

	}
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Space) {
		mModel.resetGame();
		auto Player = mModel.getCurrentPlayer();
		mView.updateStatusDisplay(Player);
	}
}

bool AIController::isBoardFull(std::span<const CellState> board) const
{
	return std::all_of(std::begin(board),
		std::end(board),
		[](auto value) {
			return value != CellState::None;
		});
}

int AIController::evaluate(std::span<const CellState> board)
{
	// Sprawdzenie wierszy
	for (int row = 0; row < 3; row++) {
		if (board[row * 3 + 0] == board[row * 3 + 1] &&
			board[row * 3 + 1] == board[row * 3 + 2]) {
			if (board[row * 3 + 0] == CellState::X) return +10;
			if (board[row * 3 + 0] == CellState::O) return -10;
		}
	}

	// Sprawdzenie kolumn
	for (int col = 0; col < 3; col++) {
		if (board[0 * 3 + col] == board[1 * 3 + col] &&
			board[1 * 3 + col] == board[2 * 3 + col]) {
			if (board[0 * 3 + col] == CellState::X) return +10;
			if (board[0 * 3 + col] == CellState::O) return -10;
		}
	}

	// Sprawdzenie diagonali
	if (board[0 * 3 + 0] == board[1 * 3 + 1] &&
		board[1 * 3 + 1] == board[2 * 3 + 2]) {
		if (board[0 * 3 + 0] == CellState::X) return +10;
		if (board[0 * 3 + 0] == CellState::O) return -10;
	}

	if (board[0 * 3 + 2] == board[1 * 3 + 1] &&
		board[1 * 3 + 1] == board[2 * 3 + 0]) {
		if (board[0 * 3 + 2] == CellState::X) return +10;
		if (board[0 * 3 + 2] == CellState::O) return -10;
	}

	return 0;
}


int AIController::minmax(std::span<CellState> board, int depth, bool isMax)
{
	int score = evaluate(board);

	if (score == 10) {
		return score;
	}

	if (score == -10) {
		return score;
	}

	if (isBoardFull(board)) {
		return 0;
	}

	if (isMax) {
		int best = -1000;

		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row * 3 + col] == CellState::None) {

					board[row * 3 + col] = CellState::X;

					best = std::max(best, minmax(board, depth + 1, !isMax));

					board[row * 3 + col] = CellState::None;
				}
			}
		}
		return best;
	}
	else {
		int best = 1000;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row * 3 + col] == CellState::None) {

					board[row * 3 + col] = CellState::O;

					best = std::min(best, minmax(board, depth + 1, !isMax));

					board[row * 3 + col] = CellState::None;
				}
			}
		}
		return best;
	}
}

std::pair<int, int> AIController::findBestMove(std::span<CellState> board)
{
	int bestValue = -1000;
	std::pair<int, int> bestMove{ -1,-1 };

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row * 3 + col] == CellState::None) {

				board[row * 3 + col] = CellState::X;

				int moveVal = minmax(board, 0, false);

				board[row * 3 + col] = CellState::None;

				if (moveVal > bestValue) {
					bestMove.first = row;
					bestMove.second = col;
					bestValue = moveVal;
				}
			}
		}
	}

	return bestMove;
}
