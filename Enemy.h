#pragma once

#include "Player.h"

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

struct Enemy {
    //attacking
    virtual void enemyAttack(Player& player, float dt) = 0;

    //animations
    virtual void updateAnimation(float dt) = 0;
    virtual void updateIdleAnimation(float dt) = 0;
    virtual void updateWalkAnimation(float dt) = 0;
    virtual void updateAttackAnimation(float dt) = 0;
    virtual void updateHitAnimation(float dt) = 0;
    virtual void updateDeadAnimation(float dt) = 0;

    //detecting
    virtual bool detectCharacter(const sf::Vector2f& playerPos) = 0;
    virtual void performBehaviourOnDetect(Player& player, float dt) = 0;

    //logic
    virtual void decreaseHP(int amount) = 0;
    virtual void move(const sf::Vector2f &direction) = 0;
    virtual void pattern1(Player& player, float dt) = 0;

    //other stuff
    virtual void render(sf::RenderWindow &window) = 0;
    virtual void update(Player& player, float dt) = 0;

    //filling frames
    virtual void fillFrameVector(sf::Texture &texture, std::vector<sf::IntRect> &frameVector, int framesCount) = 0;
    virtual void initFrames() = 0;

    virtual sf::RectangleShape getHitBox() const = 0;
    virtual int getHP() = 0;
};
