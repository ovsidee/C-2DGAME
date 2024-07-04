#pragma once

#include "Enemy.h"
#include "Player.h"


#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

struct Boss : Enemy {
    sf::Vector2f position;

    Player* player;
    //for flipping the player
    int frontFacing = -1;

    sf::Clock clock;

    sf::Vector2u windowSize;
    sf::Sprite sprite;

    //textures
    sf::Texture attackTexture;
    sf::Texture attackFlippedTexture;
    sf::Texture walkTexture;
    sf::Texture walkFlippedTexture;
    sf::Texture hitTexture;
    sf::Texture deadTexture;
    sf::Texture idleTexture;
    sf::Texture idleFlippedTexture;

    //frames
    int attackFrame = 0;
    int walkFrame = 0;
    int hitFrame = 0;
    int deadFrame = 0;
    int idleFrame = 0;

    //speed of animations
    float animationSpeed = 1.f / 8.f;
    float walkAnimationSpeed = 1.f / 10.f;
    float attackSpeed = 1.f/11.f;
    float deadSpeed = 1.f/12.f;
    float hitSpeed = 1.f/4.f;

    //time
    float timeSinceLastFrameIdle;
    float timeSinceLastFrameWalk;
    float timeSinceLastFrameAttack;
    float timeSinceLastFrameDead;
    float timeSinceLastFrameHit;

    //vector of split frames
    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> idleFlippedFrames;
    std::vector<sf::IntRect> walkFrames;
    std::vector<sf::IntRect> walkFlippedFrames;
    std::vector<sf::IntRect> attackFrames;
    std::vector<sf::IntRect> attackFlippedFrames;
    std::vector<sf::IntRect> deadFrames;
    std::vector<sf::IntRect> hitFrames;

    //for "if" action
    bool isMoving = false;
    bool isAttacking = false;
    bool isDead = false;
    bool isHit = false;
    bool isFlipped = false;
    bool isAttackFlipped = false;
    bool isDeadAnimationPlayed = false;
    bool attackPerformed = false;
    bool attackReady;
    bool isIdle = true;
    bool hasAttacked = false;
    bool hasHitAnimationCycled = false;

    // stats
    int hp = 220;
    int damageOfAttack = 10;

    //speed of actions
    float speedOfWalk = 20.f;

    //logic detecting
    float detectingRange = 2000.f;
    float attackCooldown = 1.6f;
    float lastAttackTime = attackCooldown;


    //constructor
    Boss(const sf::Vector2u& windowSize, float x , float y);

    //------------override methods
    //---- animation
    void updateAnimation(float dt) override;
    void updateIdleAnimation(float dt) override;
    void updateWalkAnimation(float dt) override;
    void updateAttackAnimation(float dt) override;
    void updateHitAnimation(float dt) override;
    void updateDeadAnimation(float dt) override;

    //---- attack
    void enemyAttack(Player& player, float dt) override;

    //---- detect
    bool detectCharacter(const sf::Vector2f& playerPos) override;
    void performBehaviourOnDetect(Player& player, float dt) override;

    //---- logic
    void decreaseHP(int amount) override;
    void initFrames() override;
    void pattern1(Player& player, float dt) override;
    void move(const sf::Vector2f &direction) override;

    //other stuff
    void render(sf::RenderWindow& window) override;
    void update(Player& player, float dt) override;

    //filling frames in vectors
    void fillFrameVector(sf::Texture &texture, std::vector<sf::IntRect> &frameVector, int framesCount);

    //getters
    sf::RectangleShape getHitBox() const;
    int getHP();
};