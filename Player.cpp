#include "Game.h"
#include "Player.h"
#include "Items.h"

//enemies
#include "Wizard.h"
#include "Bat.h"
#include "Magician.h"
#include "NightBorn.h"
#include "Boss.h"

//constructor
Player::Player(const sf::Vector2u &windowSize, float x, float y)
        : windowSize(windowSize),
          timeSinceLastFrameIdle(0.f),
          timeSinceLastFrameRun(0.f),
          timeSinceLastFrameAttack(0.f),
          timeSinceLastFrameRoll(0.f),
          timeSinceLastFrameDead(0.f),
          timeSinceLastFrameHit(0.f) {
    //loading textures
    if (!idleTexture.loadFromFile("../Character/Idle.png"))
        fmt::println("Failed to load idle texture");
    if (!runTexture.loadFromFile("../Character/Run.png"))
        fmt::println("Failed to load run texture");
    if (!defaultAttackNoMovementTexture.loadFromFile("../Character/DefaultAttackNoMOVEMENT.png"))
        fmt::println("Failed to load attack texture");
    if (!rollTexture.loadFromFile("../Character/Roll.png"))
        fmt::println("Failed to load roll texture");
    if (!deadTexture.loadFromFile("../Character/DeathNoMovement.png"))
        fmt::println("Failed to load dead texture");
    if (!hitTexture.loadFromFile("../Character/HitWhite.png"))
        fmt::println("Failed to load hit texture");

    //player
    this->sprite.setTexture(idleTexture);
    this->sprite.setPosition(x, y);
    this->sprite.setScale(2.5f, 2.0f);

    //frame
    this->initFrames();

    fmt::println("Player is initiated.");
}

//------------------methods
//checking input buttons
void Player::updateInput(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game) {
    oldPosition = this->sprite.getPosition();
    if (isHit)
        return;

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        isAttackBtnReleased = true;

    //attacking
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
        && !isAttacking
        && !isRolling && !isDead && !isHit && isAttackBtnReleased) {
        isAttacking = true;
        isAttackBtnReleased = false;
    }

    //if attacking, don`t process any other inputs
    if (isAttacking && !isDead) {
        return;
    }

    //for Moving
    if (!isRolling && !isAttacking && !isDead) {
        isMoving = false;
        // A (left)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            float leftBoundary = 0.f - additionalLeftPadding +
                                 this->movementSpeedOfPlayer;  // adjust the additionalLeftPadding as desired
            if (this->sprite.getPosition().x >= leftBoundary) {
                // Flip sprite horizontally
                if (this->sprite.getScale().x > 0) {  // We only flip if the sprite is not already flipped
                    this->sprite.setScale(-2.5f, 2.0f);
                    this->sprite.setOrigin(this->sprite.getLocalBounds().width, 0);
                }
                this->sprite.move(-this->movementSpeedOfPlayer, 0.f);
                this->sprite.setTexture(runTexture);
                isMoving = true;
//                fmt::println("Player moves left.");
            }
        }

            // D (right)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            float rightBoundary = windowSize.x - this->sprite.getGlobalBounds().width - this->movementSpeedOfPlayer -
                                  additionalRightPadding;
            if (this->sprite.getPosition().x <= rightBoundary) {
                // Reset sprite to original direction
                if (this->sprite.getScale().x < 0) {  // We only flip if the sprite is already flipped
                    this->sprite.setScale(2.5f, 2.0f);
                    this->sprite.setOrigin(0, 0);
                }
                this->sprite.move(this->movementSpeedOfPlayer, 0.f);
                this->sprite.setTexture(runTexture);
                isMoving = true;
//                fmt::println("Player moves right.");
            }
        }

        //W (up)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (this->sprite.getPosition().y - this->movementSpeedOfPlayer >= 0.f + upperVerticalPadding) {
                this->sprite.move(0.f, -this->movementSpeedOfPlayer);
                this->sprite.setTexture(runTexture);
                isMoving = true;
//                fmt::println("Player moves up.");
            }
        }

            //S (down)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height + this->movementSpeedOfPlayer <=
                windowSize.y - downVerticalPadding) {
                this->sprite.move(0.f, this->movementSpeedOfPlayer);
                this->sprite.setTexture(runTexture);
                isMoving = true;
//                fmt::println("Player moves down.");
            }
        }
    }

    // Check for collision
    switch (game->level) {
        case 0:
            if (checkCollisionForWizard(wizard) && !wizard->isDead) {
                // If collision is detected, move the player back to oldPosition
                this->sprite.setPosition(oldPosition);
            }
            if (checkCollisionForMagician(magician) && !magician->isDead) {
                this->sprite.setPosition(oldPosition);
            }
            break;
        case 1:
            if (checkCollisionForBat(bat) && !bat->isDead) {
                this->sprite.setPosition(oldPosition);
            }
            if (checkCollisionForMagician(magicianSecond) && !magicianSecond->isDead) {
                this->sprite.setPosition(oldPosition);
            }
            if (checkCollisionForNightBorn(nightBorn) && !nightBorn->isDead) {
                this->sprite.setPosition(oldPosition);
            }
            break;
        case 2:
            if (checkCollisionForBoss(boss) && !boss->isDead){
                this->sprite.setPosition(oldPosition);
            }
    }

    //for rolling (diagonal)
    if (!isRolling && !isDead) {
        //Space (roll)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            this->sprite.setTexture(rollTexture);
            isRolling = true;

            // Store the direction of roll
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                rollDirectionX = -1;
                rollDirectionY = -1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                rollDirectionX = 1;
                rollDirectionY = -1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                rollDirectionX = -1;
                rollDirectionY = 1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                rollDirectionX = 1;
                rollDirectionY = 1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                rollDirectionX = 0;
                rollDirectionY = -1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                rollDirectionX = 0;
                rollDirectionY = 1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                rollDirectionX = -1;
                rollDirectionY = 0;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                rollDirectionX = 1;
                rollDirectionY = 0;
            }
//            fmt::println("Player starts to roll.");
        }
    }

    //setting appropriate animation
    if (!isMoving && !isAttacking && !isRolling && !isDead) {
        this->sprite.setTexture(idleTexture);
    }
}

//frames in vector
void Player::initFrames() {
    fillFrameVector(idleTexture, idleFrames, 10);
    fillFrameVector(runTexture, runFrames, 10);
    fillFrameVector(defaultAttackNoMovementTexture, attackFrames, 6);
    fillFrameVector(rollTexture, rollFrames, 12);
    fillFrameVector(deadTexture, deadFrames, 10);
    fillFrameVector(hitTexture, hitFrames, 1);
    if (!idleFrames.empty())
        sprite.setTextureRect(idleFrames[0]);
}
void Player::fillFrameVector(sf::Texture& texture, std::vector<sf::IntRect>& frameVector, int framesCount) {
    sf::Vector2u textureSize = texture.getSize();
    int frameWidth = textureSize.x / framesCount;
    for (int i = 0; i < framesCount; i++)
        frameVector.emplace_back(i * frameWidth, 0, frameWidth, textureSize.y);
}

//animations
void Player::updateAnimation(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game,float dt) {
    if (!isDead) {
        updateIdleAnimation(dt);
        updateRunAnimation(dt);
        updateAttackAnimation(wizard, bat, magician, magicianSecond, nightBorn, boss, game, dt);
        updateRollAnimation(wizard, bat, magician, magicianSecond, nightBorn, boss, game, dt);
        updateHitAnimation(dt);
    } else
        updateDeadAnimation(dt);
}
void Player::updateIdleAnimation(float dt) {
    if (!isMoving && !isAttacking && !isRolling) {
        this->timeSinceLastFrameIdle += dt;
        if (this->timeSinceLastFrameIdle >= this->animationSpeed) {
            this->sprite.setTexture(this->idleTexture);
            this->timeSinceLastFrameIdle -= this->animationSpeed;
            this->idleFrame = (this->idleFrame + 1) % this->idleFrames.size();
            this->sprite.setTextureRect(this->idleFrames[this->idleFrame]);
        }
    }
}
void Player::updateRunAnimation(float dt) {
    if (isMoving && !isAttacking && !isRolling) {
        this->timeSinceLastFrameRun += dt;
        if (this->timeSinceLastFrameRun >= this->runAnimationSpeed) {
            this->sprite.setTexture(this->runTexture);
            this->timeSinceLastFrameRun -= this->runAnimationSpeed;
            this->runFrame = (this->runFrame + 1) % this->runFrames.size();
            this->sprite.setTextureRect(this->runFrames[this->runFrame]);
        }
    }
}
void Player::updateAttackAnimation(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game, float dt) {
    static bool damageApplied = false;

    if (isAttacking && !isRolling) {
        this->timeSinceLastFrameAttack += dt;
        if (this->timeSinceLastFrameAttack >= this->defaultAttackNoMovementSpeed) {
            this->sprite.setTexture(this->defaultAttackNoMovementTexture);
            this->timeSinceLastFrameAttack -= this->defaultAttackNoMovementSpeed;
            this->defaultAttackNoMovementFrame = (this->defaultAttackNoMovementFrame + 1) % this->attackFrames.size();
            this->sprite.setTextureRect(this->attackFrames[this->defaultAttackNoMovementFrame]);

            // Check for collision
            switch (game->level) {
                case 0:
                    if (!damageApplied && checkCollisionForWizard(wizard) && !wizard->isDead) {
                        wizard->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
                    if (!damageApplied && checkCollisionForMagician(magician) && !magician->isDead){
                        magician->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
                    break;
                case 1:
                    if (!damageApplied && checkCollisionForBat(bat) && !bat->isDead){
                        bat->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
                    if (!damageApplied && checkCollisionForMagician(magicianSecond) && !magicianSecond->isDead){
                        magicianSecond->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
                    if (!damageApplied && checkCollisionForNightBorn(nightBorn) && !nightBorn->isDead){
                        nightBorn->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
                    break;
                case 2:
                    if (!damageApplied && checkCollisionForBoss(boss) && !boss->isDead){
                        boss->decreaseHP(this->damageOfAttack);
                        damageApplied = true;
                    }
            }
            if (this->defaultAttackNoMovementFrame == 0) {
                this->isAttacking = false;
                damageApplied = false;  // Reset damage flag at the end of the attack
            }
        }
    }
}
void Player::updateRollAnimation(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond,NightBorn* nightBorn, Boss* boss, Game* game, float dt) {
    if (isRolling) {
        this->timeSinceLastFrameRoll += dt;
        if (this->timeSinceLastFrameRoll >= this->rollSpeed) {
            this->sprite.setTexture(this->rollTexture);
            this->timeSinceLastFrameRoll -= this->rollSpeed;
            this->rollFrame = (this->rollFrame + 1) % this->rollFrames.size();
            this->sprite.setTextureRect(this->rollFrames[this->rollFrame]);

            // Calculate potential new position
            sf::Vector2f oldPosition = this->sprite.getPosition(); // Store old position for rollback
            sf::Vector2f moveAmount(rollDirectionX * this->rollMovement, rollDirectionY * this->rollMovement);
            sf::Vector2f newPosition = oldPosition + moveAmount;

            // Check if the new position is inside the screen bounds, if yes add movement to new position
            float leftBoundary = 0.f - additionalLeftPadding;
            if (newPosition.x >= leftBoundary &&
                newPosition.x <= windowSize.x - sprite.getGlobalBounds().width - additionalRightPadding) {
                this->sprite.move(moveAmount.x, 0.f);
            }

            if (newPosition.y >= 0 + upperVerticalPadding &&
                newPosition.y <= windowSize.y - sprite.getGlobalBounds().height - downVerticalPadding) {
                this->sprite.move(0.f, moveAmount.y);
            }

            // Collision detection
            switch (game->level) {
                case 0:
                    if (checkCollisionForWizard(wizard) && !wizard->isDead) {
                        // If collision is detected, move the player back to oldPosition
                        this->sprite.setPosition(oldPosition);
                    }
                    if (checkCollisionForMagician(magician) && !magician->isDead) {
                        // If collision is detected, move the player back to oldPosition
                        this->sprite.setPosition(oldPosition);
                    }
                    break;
                case 1:
                    if (checkCollisionForBat(bat) && !bat->isDead) {
                        this->sprite.setPosition(oldPosition);
                    }
                    if (checkCollisionForMagician(magicianSecond) && !magicianSecond->isDead) {
                        // If collision is detected, move the player back to oldPosition
                        this->sprite.setPosition(oldPosition);
                    }
                    if (checkCollisionForNightBorn(nightBorn) && !nightBorn->isDead){
                        this->sprite.setPosition(oldPosition);
                    }
                    break;
                case 2:
                    if (checkCollisionForBoss(boss) && !boss->isDead){
                        this->sprite.setPosition(oldPosition);
                    }
            }
            if (this->rollFrame == 0) {
                this->isRolling = false;
                this->isMoving = false;
            }
        }
    }
}
void Player::updateDeadAnimation(float dt) {
    if (isDead && !isDeadAnimationPlayed) {
        this->timeSinceLastFrameDead += dt;
        if (this->timeSinceLastFrameDead >= this->deadAnimationSpeed) {
            this->sprite.setTexture(this->deadTexture);
            this->timeSinceLastFrameDead -= this->deadAnimationSpeed;
            this->deadFrame = (this->deadFrame + 1);

            if (this->deadFrame < this->deadFrames.size()) {
                this->sprite.setTextureRect(this->deadFrames[this->deadFrame]);
            } else {
                isDeadAnimationPlayed = true;
                deadFrame = this->deadFrames.size() - 1;   // Stick to the last frame
                this->sprite.setTextureRect(this->deadFrames[deadFrame]);
            }
        }
    }
}
void Player::updateHitAnimation(float dt) {
    if (isHit) {
        this->timeSinceLastFrameHit += dt;

        // Only update texture if necessary
        if (this->sprite.getTexture() != &this->hitTexture) {
            this->sprite.setTexture(this->hitTexture);
//            this->sprite.setColor(sf::Color::Red);
        }

        if (this->timeSinceLastFrameHit >= this->hitAnimationSpeed) {
            this->timeSinceLastFrameHit -= this->hitAnimationSpeed;
            this->hitFrame = (this->hitFrame + 1) % this->hitFrames.size();
            this->sprite.setTextureRect(this->hitFrames[this->hitFrame]);

            // If the last frame was shown, reset to idleTexture
            if ((this->hitFrame + 1) % this->hitFrames.size() == 0) {
                isHit = false;
                this->sprite.setTexture(this->idleTexture);
                this->sprite.setTextureRect(this->idleFrames[0]);
            }
        }
    }
}

//logic
void Player::decreaseHP(int damageOfAttack) {
    hp -= damageOfAttack;
    isHit = true;
    isAttacking = false;
    fmt::println("players hp {}", hp);
    if (hp <= 0) {
        hp = 0;
        isHit = false;
        isDead = true;
    }
}
bool Player::checkCollisionForWizard(Wizard* wizard) const {
    if (wizard == nullptr) {
        return false;
    }

    sf::RectangleShape playerHitBox = getHitBox();
    sf::RectangleShape enemyHitBox = wizard->getHitBox();

    return playerHitBox.getGlobalBounds().intersects(enemyHitBox.getGlobalBounds());
}
bool Player::checkCollisionForBat(Bat* bat) const {
    if (bat == nullptr) {
        return false;
    }

    sf::RectangleShape playerHitBox = getHitBox();
    sf::RectangleShape enemyHitBox = bat->getHitBox();

    return playerHitBox.getGlobalBounds().intersects(enemyHitBox.getGlobalBounds());
}
bool Player::checkCollisionForMagician(Magician* magician) const {
    if (magician == nullptr) {
        return false;
    }

    sf::RectangleShape playerHitBox = getHitBox();
    sf::RectangleShape enemyHitBox = magician->getHitBox();

    return playerHitBox.getGlobalBounds().intersects(enemyHitBox.getGlobalBounds());
}
bool Player::checkCollisionForNightBorn(NightBorn *nightBorn) const {
    if (nightBorn == nullptr) {
        return false;
    }

    sf::RectangleShape playerHitBox = getHitBox();
    sf::RectangleShape enemyHitBox = nightBorn->getHitBox();

    return playerHitBox.getGlobalBounds().intersects(enemyHitBox.getGlobalBounds());
}
bool Player::checkCollisionForBoss(Boss *boss) const {
    if (boss == nullptr) {
        return false;
    }

    sf::RectangleShape playerHitBox = getHitBox();
    sf::RectangleShape enemyHitBox = boss->getHitBox();

    return playerHitBox.getGlobalBounds().intersects(enemyHitBox.getGlobalBounds());
}
void Player::returnBack() {
    this->sprite.setPosition(oldPosition);
}
void Player::actionWithItems(Items item) {
    switch (item.getType()) {
        case ItemType::Medicine :
            hp += 15;
            fmt::println("Player`s hp  was {} -> now {}", hp-15, hp);
        break;
        case ItemType::Power :
            damageOfAttack += 5;
            fmt::println("Player`s hp  was {} -> now {}", damageOfAttack-5, damageOfAttack);
        break;
        case ItemType::Speed :
            movementSpeedOfPlayer += 0.4f;
            fmt::println("Player`s hp  was {} -> now {}", movementSpeedOfPlayer-0.4f, movementSpeedOfPlayer);
        break;
    break;
    }
}

//other stuff
void Player::update(Wizard* wizard, Bat* bat, Magician* magician, Magician* magicianSecond, NightBorn* nightBorn, Boss* boss, Game* game, float dt) {
    this->updateInput(wizard, bat, magician, magicianSecond, nightBorn, boss, game);
    this->updateAnimation(wizard, bat, magician, magicianSecond, nightBorn, boss, game, dt);
}
void Player::render(sf::RenderTarget* window) {
    window->draw(this->sprite);
//    target->draw(getHitBox());
}

//getters
sf::FloatRect Player::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}
sf::RectangleShape Player::getHitBox() const {
    sf::RectangleShape rect;
    rect.setSize({
                         -40.f,
                         -90.f
                 });
    rect.setOrigin(-170.f, -170.f); // Center the rectangle's origin
    rect.setPosition(sprite.getPosition()); // This will now center on the sprite position
    return rect;
}
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}
int Player::getHP() {
    return hp;
}