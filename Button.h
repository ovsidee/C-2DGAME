#pragma once

#include <SFML/Graphics.hpp>

struct Button {
    sf::Texture texture;
    sf::Sprite sprite;

    Button(const std::string &image_path, float x, float y, float scale_x, float scale_y);

    //methods
    void drawButton(sf::RenderWindow *window);
    bool isClicked(sf::RenderWindow* window);
};