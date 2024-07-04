#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ItemType.h"

struct Items {
    ItemType type;

    Player* player;
    sf::Sprite sprite;

    Items(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY);

    //methods
    void render(sf::RenderWindow* window);
    sf::RectangleShape setHitBox();
    bool checkCollision(Player* player);
    ItemType getType() const;
    void setType(ItemType type);
};