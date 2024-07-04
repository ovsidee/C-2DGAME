#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

struct Obstacles {
    Player* player;

    sf::Sprite sprite;

    Obstacles(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY);

    //methods
    void render(sf::RenderWindow* window);
    sf::RectangleShape setHitBox();
    bool checkCollision(Player* player);
};