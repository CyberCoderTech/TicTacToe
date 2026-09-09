#include <catch2/catch_test_macros.hpp>
#include "ResourceManager.hpp"
#include <filesystem>

TEST_CASE("ResourceManager font management", "[ResourceManager]") {
    ResourceManager resourceManager;

    SECTION("Caching: Calling getFont twice with the same path returns the same reference") {
        std::filesystem::path fontPath = "test_font.ttf";

        sf::Font& font1 = resourceManager.getFont(fontPath);
        
        sf::Font& font2 = resourceManager.getFont(fontPath);

        REQUIRE(&font1 == &font2);
    }

    SECTION("Loading different fonts returns different references") {
        std::filesystem::path fontPath1 = "test_font_1.ttf";
        std::filesystem::path fontPath2 = "test_font_2.ttf";

        sf::Font& font1 = resourceManager.getFont(fontPath1);
        sf::Font& font2 = resourceManager.getFont(fontPath2);

        REQUIRE(&font1 != &font2);
    }
}