#include <catch2/catch_test_macros.hpp>
#include <variant>
#include "mvc/BoardModel.hpp"

bool holdsPlayer(const std::variant<CellState, GameResult>& state, CellState expected) {
    return std::holds_alternative<CellState>(state) && std::get<CellState>(state) == expected;
}

bool holdsResult(const std::variant<CellState, GameResult>& state, GameResult expected) {
    return std::holds_alternative<GameResult>(state) && std::get<GameResult>(state) == expected;
}

TEST_CASE("Initialization and initial game state", "[BoardModel]") {
    BoardModel board;

    SECTION("New board must have all 9 cells set to CellState::None") {
        auto currentBoard = board.getBoard();
        REQUIRE(currentBoard.size() == 9);
        for (const auto& cell : currentBoard) {
            REQUIRE(cell == CellState::None);
        }
    }

    SECTION("At the beginning of the game the current player should be O") {
        auto state = board.getCurrentPlayer();
        REQUIRE(holdsPlayer(state, CellState::O));
    }
}

TEST_CASE("Move execution logic and turn switching", "[BoardModel]") {
    BoardModel board;

    SECTION("After a valid move by player O, the turn should switch to player X") {
        board.makeMove(0, 0);
        
        auto currentBoard = board.getBoard();
        REQUIRE(currentBoard[0] == CellState::O);
        
        auto state = board.getCurrentPlayer();
        REQUIRE(holdsPlayer(state, CellState::X));
    }

    SECTION("Move to an occupied cell should not change its state or switch the turn") {
        board.makeMove(0, 0);
        board.makeMove(0, 0);

        auto currentBoard = board.getBoard();
        REQUIRE(currentBoard[0] == CellState::O);
        
        auto state = board.getCurrentPlayer();
        REQUIRE(holdsPlayer(state, CellState::X));
    }
}

TEST_CASE("Detection of game end and results", "[BoardModel]") {
    BoardModel board;

    SECTION("Win of the first player (O) in the first row") {
        board.makeMove(0, 0);
        board.makeMove(1, 0);
        board.makeMove(0, 1);
        board.makeMove(1, 1);
        board.makeMove(0, 2);

        auto state = board.getCurrentPlayer();
        REQUIRE(holdsResult(state, GameResult::WinO));
    }

    SECTION("Win of the second player (X) diagonally") {
        board.makeMove(0, 1);
        board.makeMove(0, 0);
        board.makeMove(0, 2);
        board.makeMove(1, 1);
        board.makeMove(1, 2);
        board.makeMove(2, 2);

        auto state = board.getCurrentPlayer();
        REQUIRE(holdsResult(state, GameResult::WinX));
    }

    SECTION("Draw detection") {
        board.makeMove(0, 0);
        board.makeMove(0, 1);
        board.makeMove(0, 2);
        board.makeMove(1, 2);
        board.makeMove(1, 0);
        board.makeMove(2, 0);
        board.makeMove(1, 1);
        board.makeMove(2, 2);
        board.makeMove(2, 1);

        auto state = board.getCurrentPlayer();
        REQUIRE(holdsResult(state, GameResult::Draw));
    }
}

TEST_CASE("Resetting game state", "[BoardModel]") {
    BoardModel board;

    SECTION("After making moves, calling resetGame restores the initial state") {
        board.makeMove(0, 0);
        board.makeMove(1, 1);
        
        board.resetGame();

        auto currentBoard = board.getBoard();
        for (const auto& cell : currentBoard) {
            REQUIRE(cell == CellState::None);
        }
        
        auto state = board.getCurrentPlayer();
        REQUIRE(holdsPlayer(state, CellState::O));
    }
}


