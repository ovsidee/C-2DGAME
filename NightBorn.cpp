#include "NightBorn.h"

NightBorn::NightBorn(const sf::Vector2u &windowSize, float x, float y) :
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

    if (!idleTexture.loadFromFile("../Enemies/nightBorn/Idle.png"))
        fmt::println("Failed to load idle texture");
    if (!walkTexture.loadFromFile("../Enemies/nightBorn/Walk.png"))
        fmt::println("Failed to load walk texture");
    if (!attackTexture.loadFromFile("../Enemies/nightBorn/Attack.png"))
        fmt::println("Failed to load attack texture");
    if (!deadTexture.loadFromFile("../Enemies/nightBorn/Death.png"))
        fmt::println("Failed to load death texture");
    if (!hitTexture.loadFromFile("../Enemies/nightBorn/Hit.png"))
        fmt::println("Failed to load hit texture");

    if (!walkFlippedTexture.loadFromFile("../Enemies/nightBorn/WalkFlipped.png"))
        fmt::println("Failed to load walkHorizontal texture");
    if (!attackFlippedTexture.loadFromFile("../Enemies/nightBorn/AttackFlipped.png"))
        fmt::println("Failed to load attackFlipped texture");
    if (!idleFlippedTexture.loadFromFile("../Enemies/nightBorn/IdleFlipped.png"))
        fmt::println("Failed to load attackFlipped texture");

    //Wizard
    this->sprite.setTexture(idleTexture);
    this->sprite.setPosition(x, y);
    this->sprite.setScale(-3.4f, 3.4f);

    //frame
    this->initFrames();

    fmt::println("NightBorn is initiated.");
}

//frames into vector
void NightBorn::initFrames() {
    fillFrameVector(idleTexture, idleFrames, 9);
    fillFrameVector(walkTexture, walkFrames, 6);
    fillFrameVector(walkTexture, walkFlippedFrames, 6);
    fillFrameVector(hitTexture, hitFrames, 5);
    fillFrameVector(deadTexture, deadFrames, 23);
    fillFrameVector(attackTexture, attackFrames, 12);
    fillFrameVector(attackFlippedTexture, attackFlippedFrames, 12);
    fillFrameVector(idleFlippedTexture, idleFlippedFrames, 9);
    std::ranges::reverse(attackFlippedFrames);
    std::ranges::reverse(walkFlippedFrames);
    std::ranges::reverse(idleFlippedFrames);
}
void NightBorn::fillFrameVector(sf::Texture &texture, std::vector<sf::IntRect> &frameVector, int framesCount) {
    sf::Vector2u textureSize = texture.getSize();
    int frameWidth = textureSize.x / framesCount;
    for (int i = 0; i < framesCount; ++i) {
        frameVector.emplace_back(i * frameWidth, 0, frameWidth, textureSize.y);
    }
}

//animations
void NightBorn::updateAnimation(float dt) {
    updateIdleAnimation(dt);
    updateWalkAnimation(dt);
    updateAttackAnimation(dt);
    updateHitAnimation(dt);
    updateDeadAnimation(dt);
}
void NightBorn::updateIdleAnimation(float dt) {
    if(!isMoving && !isAttacking && !isDead && !isHit) {
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
void NightBorn::updateWalkAnimation(float dt) {
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
void NightBorn::updateDeadAnimation(float dt) {
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
void NightBorn::updateHitAnimation(float dt) {
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
void NightBorn::updateAttackAnimation(float dt) {
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
//            fmt::print("NightBorn Attacking\n");
        }
    }
}

// Perform Attack
void NightBorn::enemyAttack(Player& player, float dt) {
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
void NightBorn::decreaseHP(int damageOfAttack) {
    if(!isDead) {
        hp -= damageOfAttack;
        fmt::println("NightBorn hp {}", hp);
        if (hp <= 0) {
            hp = 0;
            isDead = true;
            fmt::println("NightBorn is dead");
        } else {
            isHit = true; // Set isHit to true when the wizard gets hit
        }
    }
}

// Perform Behavior when detected
void NightBorn::performBehaviourOnDetect(Player& player, float dt) {
    if (!isDead && !isHit) {
        sf::RectangleShape nightBornHitbox = getHitBox();
        sf::RectangleShape playerHitbox = player.getHitBox();

        bool isAtAttackRange = nightBornHitbox.getGlobalBounds().intersects(playerHitbox.getGlobalBounds());

        if (isAtAttackRange && !hasAttacked && attackReady) {
//            fmt::println("Player is in attack range. NightBorn will attack");
            enemyAttack(player, dt);
            if (attackPerformed) {
                isAttacking = true;
                isMoving = false;
                attackPerformed = false;
            }
        } else if (!isAtAttackRange){
//            fmt::println("Player is not in attack range. NightBorn will move.");
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

bool NightBorn::detectCharacter(const sf::Vector2f& playerPos) {
    sf::Vector2f nightBornPos = this->sprite.getPosition();

    float distanceX = abs(playerPos.x - nightBornPos.x);
    float distanceY = abs(playerPos.y - nightBornPos.y);

    return distanceX <= detectingRange && distanceY <= detectingRange;
}
void NightBorn::pattern1(Player& player, float dt) {
    constexpr float speedX = 180.0f;

    sf::RectangleShape nightBornHitbox = getHitBox();
    sf::RectangleShape playerHitbox = player.getHitBox();

    sf::Vector2f nightBornPos = nightBornHitbox.getPosition();

    bool isAtAttackRange = nightBornHitbox.getGlobalBounds().intersects(playerHitbox.getGlobalBounds());

    static int directionX = 1;

    const float leftLimit = 400.0f;
    const float rightLimit = 1250.0f;

    if (!isDead && !isAttacking && isMoving) {
        if (!isAtAttackRange) {
            if (nightBornPos.x <= leftLimit && directionX == -1) {
                fmt::println("NightBorn Going right(back)");
                isFlipped = true;
                isAttackFlipped = true;
                directionX = 1;
                isMoving = true;
                isAttacking = false;
            } else if (nightBornPos.x >= rightLimit && directionX == 1) {
                fmt::println("NightBorn Going left(from the spawn)");
                isFlipped = false;
                isAttackFlipped = false;
                directionX = -1;
                isMoving = true;
                isAttacking = false;
            }
            nightBornPos.x += speedX * directionX * dt;
            sprite.setPosition(nightBornPos);
        } else if (isAtAttackRange && !hasAttacked) { // Check ability to attack
            fmt::println("NightBorn Attacking player...");
            enemyAttack(player, dt);
            if (attackPerformed) {
                attackPerformed = false; // Reset attack performed flag
                isAttacking = true;
                isMoving = false;
            }
        } else if (isAtAttackRange && hasAttacked) {
            fmt::println("NightBorn stay in range but can't attack");
            hasAttacked = false;  // Reset ability to attack
            return;
        }
        updateAnimation(dt);
    }
}
void NightBorn::update(Player& player, float dt) {
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
void NightBorn::render(sf::RenderWindow &window) {
    window.draw(this->sprite);
//    window.draw(getHitBox());
}
void NightBorn::move(const sf::Vector2f &direction) {
    this->isMoving = true;
    this->sprite.move(direction * speedOfWalk);
}

//getters
sf::RectangleShape NightBorn::getHitBox() const {
    sf::RectangleShape rect;
    rect.setSize({
                         70.f,
                         110.f
                 });
    rect.setOrigin(185.f, -60.f); // Center the rectangle's origin
    rect.setPosition(sprite.getPosition()); // This will now center on the sprite position
    return rect;
}
int NightBorn::getHP() {
    return hp;
}