#include "Items.h"

Items::Items(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY) {
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
}

bool Items::checkCollision(Player* player) {
    sf::RectangleShape playerHitBox = player->getHitBox();
    sf::RectangleShape obstacleHitBox = setHitBox();

    return playerHitBox.getGlobalBounds().intersects(obstacleHitBox.getGlobalBounds());
}

void Items::render(sf::RenderWindow *window) {
    window->draw(sprite);
//    window->draw(setHitBox());
}
sf::RectangleShape Items::setHitBox() {
    sf::RectangleShape rect;
    rect.setSize({
                         -20.f,
                         -40.f
                 });
    rect.setOrigin(-30.f, -45.f); // Center the rectangle's origin
    rect.setPosition(sprite.getPosition()); // This will now center on the sprite position
    rect.setFillColor(sf::Color::Red);
    return rect;
}

//getters
ItemType Items::getType() const {
    return type;
}

//set
void Items::setType(ItemType type) {
    this->type = type;
}