#pragma once

#include <iostream>
#include <fmt/ranges.h>
#include <SFML/Graphics.hpp>

class Wizard;
class Bat;
class Magician;
class NightBorn;
class Boss;

class Game;
class Items;

struct Player {

    //window
    sf::Vector2u windowSize;

    //sprite
    sf::Sprite sprite;

    //collision
    float additionalLeftPadding = 100.0f;
    float additionalRightPadding = 10.0f;
    float upperVerticalPadding = 170.0f;
    float downVerticalPadding = 110.0f;

    //textures
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture defaultAttackNoMovementTexture;
    sf::Texture rollTexture;
    sf::Texture deadTexture;
    sf::Texture hitTexture;

    //frames
    int idleFrame = 0;
    int runFrame = 0;
    int defaultAttackNoMovementFrame = 0;
    int rollFrame = 0;
    int deadFrame = 0;
    int hitFrame = 0;

    //speed of animations
    float animationSpeed = 1.f/10.f;
    float runAnimationSpeed = 1.f/10.f;
    float defaultAttackNoMovementSpeed = 1.f/10.f;
    float deadAnimationSpeed = 1.f / 9.f;
    float hitAnimationSpeed = 1.f / 2.f;

    //speed of movement
    float rollMovement = 20.f;
    float movementSpeedOfPlayer = 7.0f;
    float rollSpeed = 1.f/25.f;

    //coordinates for roll
    float rollDirectionX = 0;
    float rollDirectionY = 0;

    //time
    float timeSinceLastFrameIdle;
    float timeSinceLastFrameRun;
    float timeSinceLastFrameAttack;
    float timeSinceLastFrameRoll;
    float timeSinceLastFrameDead;
    float timeSinceLastFrameHit;

    //vector of split frames
    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> runFrames;
    std::vector<sf::IntRect> attackFrames;
    std::vector<sf::IntRect> rollFrames;
    std::vector<sf::IntRect> deadFrames;
    std::vector<sf::IntRect> hitFrames;
    std::vector<sf::Sprite> hpSprites;

    //checking actions
    bool isMoving = false;
    bool isAttacking = false;
    bool isRolling = false;
    bool isDead = false;
    bool isDeadAnimationPlayed = false;
    bool isHit = false;
    bool isAttackBtnReleased = false;
    bool hitAnimationPlayed = false;

    // player stats
    int hp = 100;
    int damageOfAttack = 15;

    //collision
    sf::Vector2f oldPosition;

    //constructor
    Player(const sf::Vector2u& windowSize, float x = 496.f, float y = 440.f);

    //----------------methods
    //frames
    void fillFrameVector(sf::Texture &texture, std::vector<sf::IntRect> &frameVector, int framesCount);
    void initFrames();

    //keyboard inputs
    void updateInput(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game);

    //collision
    bool checkCollisionForWizard(Wizard* wizard) const;
    bool checkCollisionForBat(Bat* bat) const;
    bool checkCollisionForMagician(Magician* magician) const;
    bool checkCollisionForNightBorn(NightBorn* nightBorn) const;
    bool checkCollisionForBoss(Boss* boss) const;
    void returnBack();

    //items
    void actionWithItems(Items item);

    //animations
    void updateAnimation(Wizard* wizard, Bat *bat, Magician *magician, Magician* magicianSecond,NightBorn* nightBorn, Boss* boss, Game* game, float dt);
    void updateIdleAnimation(float dt);
    void updateRunAnimation(float dt);
    void updateAttackAnimation(Wizard* wizard, Bat *bat, Magician *magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game, float dt);
    void updateRollAnimation(Wizard* wizard, Bat *bat, Magician *magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game, float dt);
    void updateDeadAnimation(float dt);
    void updateHitAnimation(float dt);

    //other stuff
    void update(Wizard* wizard, Bat *bat, Magician *magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game, float dt);
    void render(sf::RenderTarget* target);

    //hp
    void decreaseHP(int damageOfAttack);

    //getters
    sf::RectangleShape getHitBox() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    int getHP();
};
