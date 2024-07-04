#include "Obstacles.h"

Obstacles::Obstacles(const sf::Texture& texture, float posX, float posY, float scaleX, float scaleY) {
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
}

bool Obstacles::checkCollision(Player* player) {
    sf::RectangleShape playerHitBox = player->getHitBox();
    sf::RectangleShape obstacleHitBox = setHitBox();

    return playerHitBox.getGlobalBounds().intersects(obstacleHitBox.getGlobalBounds());
}

void Obstacles::render(sf::RenderWindow *window) {
    window->draw(sprite);
//    window->draw(setHitBox());
}
sf::RectangleShape Obstacles::setHitBox() {
    sf::RectangleShape rect;
    rect.setSize({
                         -90.f,
                         -100.f
                 });
    rect.setOrigin(-110.f, -135.f); // Center the rectangle's origin
    rect.setPosition(sprite.getPosition()); // This will now center on the sprite position
    return rect;
}