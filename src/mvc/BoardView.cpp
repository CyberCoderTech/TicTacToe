#include<type_traits>
#include<algorithm>
#include<cmath>

#include "mvc/BoardView.hpp"


BoardView::BoardView(sf::RenderWindow& argWindow,const sf::Font& textFont):window(argWindow)
{
	topRectangle.setFillColor(sf::Color::Transparent);
	topRectangle.setOutlineColor(sf::Color::White);
	topRectangle.setOutlineThickness(2.f);
	topRectangle.setPosition(sf::Vector2f{
			2.f,2.f
		});
	topRectangle.setSize(sf::Vector2f{
			argWindow.getSize().x-4.f,
			argWindow.getSize().y*0.13f
		});

	areaBoard.left = 0.f;
	areaBoard.top = topRectangle.getSize().y + 4.f;
	areaBoard.width = argWindow.getSize().x;
	areaBoard.height = argWindow.getSize().y * 0.87f;
	
	text.setFont(textFont);
	text.setString("Round:O");
	text.setPosition(sf::Vector2f{
		 8.f,5.f
		});

	resetGame.setFont(textFont);
	resetGame.setString("Space - Reset Game");
	resetGame.setPosition(sf::Vector2f{
		150.f,5.f
		});

	backToMenu.setFont(textFont);
	backToMenu.setString("Escape - Back To Menu");
	backToMenu.setPosition(sf::Vector2f{
		460.f,5.f
		});

	separateLine[0].color = sf::Color::White;
	separateLine[0].position = sf::Vector2f(138.f, 0.f);
	separateLine[1].color = sf::Color::White;
	separateLine[1].position = sf::Vector2f(138.f, 54.f);
}

void BoardView::updateSize(const int newWidth, const int newHeight)
{
	window.setView(sf::View(sf::FloatRect(0, 0, newWidth, newHeight)));
	topRectangle.setSize(sf::Vector2f{
		newWidth - 4.f,
		newHeight * 0.13f
		});


	areaBoard.left = 0.f;
	areaBoard.top = topRectangle.getSize().y + 4.f;
	areaBoard.width = newWidth;
	areaBoard.height = newHeight * 0.87f;

	float scaleWidth = newWidth / static_cast<float>(BASE_WIDTH_WINDOW);
	float scaleHeight = newHeight / static_cast<float>(BASE_HEIGHT_WINDOW);

	float scale = std::min(scaleWidth, scaleHeight);
	
	scale = std::clamp(scale, 0.75f, 3.0f);

	text.setCharacterSize(
		std::max(1u,static_cast<unsigned int>(std::round(BASE_FONT_SIZE * scale)))
	);

}

void BoardView::updateStatusDisplay(std::variant<CellState, GameResult> player)
{
	std::visit([&](auto&& arg) 
	{
		using TypeLogicMessage = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<TypeLogicMessage, GameResult>) {
			switch (arg) {
			case GameResult::WinO:{
				text.setString("Winner O");
			}break;
			case GameResult::WinX: {
				text.setString("Winner X");
			}break;
			case GameResult::Draw: {
				text.setString("Draw");
			}break;
		  }
		}
		else if constexpr (std::is_same_v<TypeLogicMessage, CellState>) {
			switch (arg) {
			case CellState::X: {
				text.setString("Round X");
			}break;
			case CellState::O: {
				text.setString("Round O");
			}break;

			}
		}
		
	}, player);
}

sf::Vector2i BoardView::getBoardCoordinates(const sf::Vector2f mousePos)
{
	if (areaBoard.contains(mousePos)) {

		auto CellWidth = areaBoard.width / 3.f;
		auto CellHeight = areaBoard.height / 3.f;

		float localX = mousePos.x - areaBoard.left;
		float localY = mousePos.y - areaBoard.top;

		sf::Vector2i cordinate{
			static_cast<int>(localX / CellWidth),
			static_cast<int>(localY/CellHeight)
		};

		return cordinate;

	}
	return sf::Vector2i();
}



void BoardView::draw(std::span<const CellState> board)
{
	window.clear();
	window.draw(topRectangle);
	window.draw(text);
	window.draw(resetGame);
	window.draw(backToMenu);
	window.draw(separateLine.data(),2, sf::Lines);
	drawGrid();

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row + 3 * col] == CellState::O) {

				float CellW = areaBoard.width / 3.f;
				float CellH = areaBoard.height / 3.f;
				float sizeCell = std::min(CellW, CellH);
				float margin = sizeCell * 0.22f;
				float thicknes = sizeCell * 0.08f;

				float radius = (sizeCell - margin) / 2.f;

				sf::Vector2f center{
					areaBoard.left + col * CellW + CellW / 2.f,
					areaBoard.top + row * CellH + CellH / 2.f
				};

				sf::CircleShape circle;
				circle.setRadius(radius - thicknes / 2.f);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				circle.setFillColor(sf::Color::Transparent);
				circle.setOutlineColor(sf::Color::Red);
				circle.setOutlineThickness(thicknes);
				circle.setPosition(center);

				window.draw(circle);

			}
			else if (board[row + 3 * col] == CellState::X) {
				float CellW = areaBoard.width / 3.f;
				float CellH = areaBoard.height / 3.f;
				float sizeCell = std::min(CellW, CellH);
				float thicknes = sizeCell * 0.08f;

				sf::Vector2f center(
					areaBoard.left + col * CellW + CellW / 2.f,
					areaBoard.top + row * CellH + CellH / 2.f
				);

				sf::RectangleShape line1({ sizeCell, thicknes });
				sf::RectangleShape line2({ sizeCell, thicknes });

				line1.setOrigin(sizeCell / 2.f, thicknes / 2.f);
				line2.setOrigin(sizeCell / 2.f, thicknes / 2.f);

				line1.setPosition(center);
				line2.setPosition(center);

				line1.setRotation(45.f);
				line2.setRotation(-45.f);

				line1.setFillColor(sf::Color::Cyan);
				line2.setFillColor(sf::Color::Cyan);

				window.draw(line1);
				window.draw(line2);

			}
		}
	}

	window.display();
}

void BoardView::drawGrid()
{
	float cellWidth = areaBoard.width / 3.f;
	float cellHeight = areaBoard.height / 3.f;

	for (int i = 1; i < 3; ++i) {
		sf::Vertex verticalLine[] = {
			sf::Vertex({areaBoard.left + i * cellWidth,areaBoard.top}),
			sf::Vertex({areaBoard.left+i*cellWidth,areaBoard.top+areaBoard.height})
		};

		window.draw(verticalLine, 2, sf::Lines);

		sf::Vertex horizontalLine[] = {
			sf::Vertex({areaBoard.left,areaBoard.top + i * cellHeight}),
			sf::Vertex({areaBoard.left + areaBoard.width,areaBoard.top + i * cellHeight})
		};
		window.draw(horizontalLine, 2, sf::Lines);

	}
}
