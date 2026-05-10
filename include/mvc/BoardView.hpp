#pragma once

#include<SFML/Graphics.hpp>

#include"BoardModel.hpp"

constexpr int BASE_WIDTH_WINDOW = 640;
constexpr int BASE_HEIGHT_WINDOW = 320;
constexpr int BASE_FONT_SIZE = 30;

class BoardView {
public:
	BoardView(sf::RenderWindow&,const sf::Font&);
	~BoardView() = default;

	void updateSize(const int newWidth, const int newHeight);

	sf::Vector2i getBoardCoordinates(const sf::Vector2f mousePos);
	void updateStatusDisplay(std::variant<CellState, GameResult> player);

	void draw(std::span<const CellState> board);
private:
	sf::RenderWindow& window;

	sf::RectangleShape topRectangle;
	std::array<sf::Vertex, 2> separateLine;
	sf::FloatRect areaBoard;

	sf::Text text;
	sf::Text resetGame;
	sf::Text backToMenu;

	void drawGrid();
};