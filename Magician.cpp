#include "Magician.h"

Magician::Magician(const sf::Vector2u &windowSize, float x, float y) :
        windowSize(windowSize),
        speedOfWalk(1.9f),
        timeSinceLastFrameIdle(0.f),
        timeSinceLastFrameWalk(0.f),
        timeSinceLastFrameAttack(0.f),
        timeSinceLastFrameDead(0.f),
        timeSinceLastFrameHit(0.f),
        player(nullptr)
{
    lastAttackTime = attackCooldown;
    attackReady = true;
    clock.restart();
    if (!idleTexture.loadFromFile("../Enemies/magicianUSED/Idle.png"))
        fmt::println("Failed to load idle texture");
    if (!walkTexture.loadFromFile("../Enemies/magicianUSED/Walk.png"))
        fmt::println("Failed to load walk texture");
    if (!attackTexture.loadFromFile("../Enemies/magicianUSED/Attack.png"))
        fmt::println("Failed to load attack texture");
    if (!deadTexture.loadFromFile("../Enemies/magicianUSED/Death.png"))
        fmt::println("Failed to load death texture");
    if (!hitTexture.loadFromFile("../Enemies/magicianUSED/Hit.png"))
        fmt::println("Failed to load hit texture");

    if (!walkFlippedTexture.loadFromFile("../Enemies/magicianUSED/WalkFlipped.png"))
        fmt::println("Failed to load walkHorizontal texture");
    if (!attackFlippedTexture.loadFromFile("../Enemies/magicianUSED/AttackFlipped.png"))
        fmt::println("Failed to load attackFlipped texture");
    if (!idleFlippedTexture.loadFromFile("../Enemies/magicianUSED/IdleFlipped.png"))
        fmt::println("Failed to load idleFlipped texture");

    //Wizard
    this->sprite.setTexture(idleTexture);
    this->sprite.setPosition(x, y);
    this->sprite.setScale(-1.5f, 1.5f);

    //frame
    this->initFrames();

    fmt::println("Magician is initiated.");
}

//frames into vector
void Magician::initFrames() {
    fillFrameVector(idleTexture, idleFrames, 6);
    fillFrameVector(walkTexture, walkFrames, 8);
    fillFrameVector(walkTexture, walkFlippedFrames, 8);
    fillFrameVector(hitTexture, hitFrames, 4);
    fillFrameVector(deadTexture, deadFrames, 7);
    fillFrameVector(attackTexture, attackFrames, 8);
    fillFrameVector(attackFlippedTexture, attackFlippedFrames, 8);
    fillFrameVector(idleFlippedTexture, idleFlippedFrames, 6);

    std::ranges::reverse(attackFlippedFrames);
    std::ranges::reverse(walkFlippedFrames);
    std::ranges::reverse(idleFlippedFrames);
}
void Magician::fillFrameVector(sf::Texture &texture, std::vector<sf::IntRect> &frameVector, int framesCount) {
    sf::Vector2u textureSize = texture.getSize();
    int frameWidth = textureSize.x / framesCount;
    for (int i = 0; i < framesCount; ++i) {
        frameVector.emplace_back(i * frameWidth, 0, frameWidth, textureSize.y);
    }
}

//animations
void Magician::updateAnimation(float dt) {
    updateIdleAnimation(dt);
    updateWalkAnimation(dt);
    updateAttackAnimation(dt);
    updateHitAnimation(dt);
    updateDeadAnimation(dt);
}
void Magician::updateIdleAnimation(float dt) {
    if (!isMoving && !isAttacking && !isDead && !isHit) {
        this->timeSinceLastFrameIdle += dt;
        if (this->timeSinceLastFrameIdle >= this->animationSpeed) {
            if (isFlipped) {
                this->sprite.setTexture(this->idleFlippedTexture);
                this->idleFrame = (this->idleFrame + 1) % this->idleFlippedFrames.size();
                this->sprite.setTextureRect(this->idleFlippedFrames[this->idleFrame]);
            } else {
                this->sprite.setTexture(this->idleTexture);
                this->idleFrame = (this->idleFrame + 1) % this->idleFrames.size();
                this->sprite.setTextureRect(this->idleFrames[this->idleFrame]);
            }
            this->timeSinceLastFrameIdle -= this->animationSpeed;
        }
    }
}
void Magician::updateWalkAnimation(float dt) {
    if(isMoving && !isAttacking && !isDead) {
        this->timeSinceLastFrameWalk += dt;
        if (this->timeSinceLastFrameWalk >= this->walkAnimationSpeed) {
            if (isFlipped) {
                this->sprite.setTexture(this->walkFlippedTexture);
            } else {
                this->sprite.setTexture(this->walkTexture);
            }
            this->timeSinceLastFrameWalk -= this->walkAnimationSpeed;
            this->walkFrame = (this->walkFrame + 1) % this->walkFrames.size();
            this->sprite.setTextureRect(this->walkFrames[this->walkFrame]);
        }
    }
}
void Magician::updateDeadAnimation(float dt) {
    if(isDead && !isDeadAnimationPlayed) {
        this->timeSinceLastFrameDead += dt;
        if (this->timeSinceLastFrameDead >= this->deadSpeed) {
            this->sprite.setTexture(this->deadTexture);
            this->timeSinceLastFrameDead -= this->deadSpeed;

            // This part achieves a similar function as to the Player class
            this->deadFrame = (this->deadFrame + 1);

            // Check if we have more frames to go through
            if (this->deadFrame < this->deadFrames.size()) {
                this->sprite.setTextureRect(this->deadFrames[this->deadFrame]);
            } else {
                // If we've gone through all frames, then stop the animation
                isDeadAnimationPlayed = true;
                deadFrame = this->deadFrames.size() - 1;   // Stick to the last frame
                this->sprite.setTextureRect(this->deadFrames[deadFrame]);
            }
        }
    }
}
void Magician::updateHitAnimation(float dt) {
    if(isHit && !isDead) {
        this->timeSinceLastFrameHit += dt;
        if (this->timeSinceLastFrameHit >= this->hitSpeed) {
            this->sprite.setTexture(this->hitTexture);
            this->timeSinceLastFrameHit -= this->hitSpeed;
            this->hitFrame = (this->hitFrame + 1) % this->hitFrames.size();
            this->sprite.setTextureRect(this->hitFrames[this->hitFrame]);
            // If we've cycled round to the first frame, mark the animation as having cycled
            if (this->hitFrame == 0 && !this->hasHitAnimationCycled) {
                this->hasHitAnimationCycled = true;
            }
                // If we've completed a full cycle of the hit animation, stop the hit
            else if(this->hitFrame == 0 && this->hasHitAnimationCycled) {
                isHit = false;
                // Reset the flag for next hit animation
                this->hasHitAnimationCycled = false;
            }
        }
    }
}
void Magician::updateAttackAnimation(float dt) {
    if (isAttacking && !isDead && !isHit) {
        this->timeSinceLastFrameAttack += dt;
        if (this->timeSinceLastFrameAttack >= this->attackSpeed) {
            if (isAttackFlipped) {
                this->sprite.setTexture(this->attackFlippedTexture);
                this->attackFrame = (this->attackFrame + 1) % this->attackFlippedFrames.size();
                this->sprite.setTextureRect(this->attackFlippedFrames[this->attackFrame]);
            } else {
                this->sprite.setTexture(this->attackTexture);
                this->attackFrame = (this->attackFrame + 1) % this->attackFrames.size();
                this->sprite.setTextureRect(this->attackFrames[this->attackFrame]);
            }
            this->timeSinceLastFrameAttack -= this->attackSpeed;

            if (this->attackFrame == 0) { // once the animation has looped once
                isAttacking = false; // stop attacking
            }
//            fmt::print("Magician Attacking\n");
        }
    }
}

// Perform Attack
void Magician::enemyAttack(Player& player, float dt) {
    if(!isDead && !isHit) {
        if (attackReady) {
            player.decreaseHP(this->damageOfAttack);
            hasAttacked = true;
            isAttacking = false;
            attackPerformed = true;
            lastAttackTime = 0; // Reset the time since last attack.
            attackReady = false; // Set attack back to not ready.
        }
    }
}
void Magician::decreaseHP(int damageOfAttack) {
    if(!isDead) {
        hp -= damageOfAttack;
        fmt::println("magician hp {}", hp);
        if (hp <= 0) {
            hp = 0;
            isDead = true;
            fmt::println("Magician is dead");
        } else {
            isHit = true; // Set isHit to true when the wizard gets hit
        }
    }
}

// Perform Behavior when detected
void Magician::performBehaviourOnDetect(Player& player, float dt) {
    if (!isDead && !isHit) {
        sf::RectangleShape wizardHitbox = getHitBox();
        sf::RectangleShape playerHitbox = player.getHitBox();

        const bool isAtAttackRange = wizardHitbox.getGlobalBounds().intersects(playerHitbox.getGlobalBounds());

        if (isAtAttackRange && !hasAttacked && attackReady) {
//            fmt::println("Player is in attack range. Magician will attack");
            enemyAttack(player, dt);
            if (attackPerformed) {
                isAttacking = true;
                isMoving = false;
                attackPerformed = false;
            }
        } else if (!isAtAttackRange){
//            fmt::println("Player is not in attack range. Magician will move.");
            hasAttacked = false;
            isAttacking = false;
            isMoving = true;
            pattern1(player, dt);
        }
        if (attackReady) {
            hasAttacked = false;
            isAttacking = false;
        }
    } else {
        isAttacking = false;
        isMoving = false;
    }
    updateAnimation(dt);
}

bool Magician::detectCharacter(const sf::Vector2f& playerPos) {
    sf::Vector2f magicianPos = this->sprite.getPosition();

    float distanceX = abs(playerPos.x - magicianPos.x);
    float distanceY = abs(playerPos.y - magicianPos.y);

    return distanceX <= detectingRange && distanceY <= detectingRange;
}
void Magician::pattern1(Player& player, float dt) {
    constexpr float speedX = 180.0f;

    sf::RectangleShape magicianHitbox = getHitBox();
    sf::RectangleShape playerHitbox = player.getHitBox();

    sf::Vector2f magicianPos = magicianHitbox.getPosition();

    bool isAtAttackRange = magicianHitbox.getGlobalBounds().intersects(playerHitbox.getGlobalBounds());

    static int directionX = 1;
    //TODO CHANGE LIMITS TO OBSTACLES
    const float leftLimit = 400.0f;
    const float rightLimit = 1250.0f;

    if (!isDead && !isAttacking && isMoving) {
        if (!isAtAttackRange) {
            if (magicianPos.x <= leftLimit && directionX == -1) {
                fmt::println("Magician Going right(back)");
                isFlipped = true;
                isAttackFlipped = true;
                directionX = 1;
                isMoving = true;
                isAttacking = false;
            } else if (magicianPos.x >= rightLimit && directionX == 1) {
                fmt::println("Magician Going left(from the spawn)");
                isFlipped = false;
                isAttackFlipped = false;
                directionX = -1;
                isMoving = true;
                isAttacking = false;
            }
            magicianPos.x += speedX * directionX * dt;
            sprite.setPosition(magicianPos);
        } else if (isAtAttackRange && !hasAttacked) { // Check ability to attack
            fmt::println("Magician Attacking player...");
            enemyAttack(player, dt);
            if (attackPerformed) {
                attackPerformed = false; // Reset attack performed flag
                isAttacking = true;
                isMoving = false;
            }
        } else if (isAtAttackRange && hasAttacked) {
            fmt::println("Magician stay in range but can't attack");
            hasAttacked = false;  // Reset ability to attack
            return;
        }
        updateAnimation(dt);
    }
}
void Magician::update(Player& player, float dt) {
    if (lastAttackTime < attackCooldown) {
        lastAttackTime += dt;
    } else {
        attackReady = true;
    }

    sf::Vector2f playerPos = player.getPosition();

    if (!isDead && !isIdle && !isAttacking) {
        performBehaviourOnDetect(player, dt);
    }else if (isHit){
        this->isIdle = false;
        this->isMoving = false;
        this->isDeadAnimationPlayed = false;
        this->isAttacking = false;
    }
    else if (detectCharacter(playerPos)) {
        this->isIdle = false;
    } else {
        this->isIdle = true;
    }
    sf::Time elapsed = clock.restart();
    updateAnimation(elapsed.asSeconds());
}

//other stuff
void Magician::render(sf::RenderWindow &window) {
    window.draw(this->sprite);
//    window.draw(getHitBox());
}
void Magician::move(const sf::Vector2f &direction) {
    this->isMoving = true;
    this->sprite.move(direction * speedOfWalk);
}

//getters
sf::RectangleShape Magician::getHitBox() const {
    sf::RectangleShape rect;
    rect.setSize({
                         70.f,
                         110.f
                 });
    rect.setOrigin(185.f, -90.f); // Center the rectangle's origin
    rect.setPosition(sprite.getPosition()); // This will now center on the sprite position
    return rect;
}
int Magician::getHP() {
    return hp;
}