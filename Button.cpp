#include "Button.h"
#include <iostream>
#include <fmt/ranges.h>

Button::Button (const std::string& image_path, float x, float y, float scale_x, float scale_y) {
    if (!texture.loadFromFile(image_path))
        fmt::println("Failed to load button texture! {}" , image_path);
    else {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(scale_x, scale_y);
    }
}

void Button::drawButton(sf::RenderWindow* window) {
    window->draw(sprite);
}

bool Button::isClicked(sf::RenderWindow* window) {
    // Get current mouse position relative to the window
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    // Convert it to world coordinates, especially necessary if using views
    sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);

    // Check if mouse is within button boundaries
    return sprite.getGlobalBounds().contains(worldPos);
}
