#include "Game.h"
#include "Player.h"

#include <random>
#include <thread>
// Initialize Window
void Game::initWindow(){
    this->videoMode = sf::VideoMode(1280, 720);
    this->window = new sf::RenderWindow(this->videoMode, "Elden Ring DLC",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);

}

// Game constructor \ destructor
Game::Game()
        : window(nullptr),
          player(sf::Vector2u(1280, 720), -70.f, 300.f)
{
    if (!hpTexture.loadFromFile("../Character/hpOnce.png"))
        fmt::println("Failed to load heart texture");

    hpSprite.setTexture(hpTexture);
    this->initWindow();
    this->initVariables();
    clock.restart();

    // Initialize playerCenter
    this->playerCenter = this->player.sprite.getPosition();

    switchLevels(level);

}
Game::~Game() {
    delete this->window;
    //prevent memory leak
    delete wizard;
    delete bat;
    delete magician;
    delete magician1;
    delete nightBorn;
    delete boss;
}

//methods
void Game::initVariables() {
    this->endGame = false;

    if (!font.loadFromFile("../Font/LoudnoiseBlack.ttf")) {
        fmt::println("Failed to load font");
    } else {
        // Initialize text objects
        gameOverText = createText("GAME OVER", 100, sf::Color::Red, {0.0f, 0.0f});
        gameOverText.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 - 30);

        toMenuText = createText("GOING BACK TO THE MENU...", 70, sf::Color::Red, {0.0f, 0.0f});
        toMenuText.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2 + toMenuText.getLocalBounds().height - 10);

        hpIncreasedText = createText("HP Increased!", 30, sf::Color::Yellow, {0.0f, 0.0f});
        hpIncreasedText.setPosition(this->window->getSize().x / 2 - 470.f, this->window->getSize().y / 2 + hpIncreasedText.getLocalBounds().height - 230);

        nextLevelText = createText("Press \"M\" to go to the next level", 30, sf::Color::Yellow, {0.0f, 0.0f});
        nextLevelText.setPosition(this->window->getSize().x / 2 - 240.f, this->window->getSize().y / 2 + nextLevelText.getLocalBounds().height - 230);

        speedIncreasedText = createText("Speed Increased!", 30, sf::Color::Yellow, {0.0f, 0.0f});
        speedIncreasedText.setPosition(this->window->getSize().x / 2 - 450.f, this->window->getSize().y / 2 + speedIncreasedText.getLocalBounds().height - 230);

        powerOfAttackIncreasedText = createText("Power Increased!", 30, sf::Color::Yellow, {0.0f, 0.0f});
        powerOfAttackIncreasedText.setPosition(this->window->getSize().x / 2 - 450.f, this->window->getSize().y / 2 + powerOfAttackIncreasedText.getLocalBounds().height - 230);
    }
}
sf::Text Game::createText(const std::string& string, int size, const sf::Color& fillColor, const sf::Vector2f& position) {
    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(fillColor);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setPosition(position);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    return text;
}

bool Game::running() const {
    return this->window->isOpen();
}
void Game::pollEvents() {
    while (this->window->pollEvent(this->sfmlEvent)){
        switch (this->sfmlEvent.type) {
            case sf::Event::Closed :
                this->window->close();
                break;
            case sf::Event::KeyPressed :
                if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                switch (level) {
                    case 0:
                        if (wizard->isDead && magician->isDead && this->sfmlEvent.key.code == sf::Keyboard::M) {
                            this->level++;
                            backgroundTexture = sf::Texture();
                            backgroundSprite = sf::Sprite();
                            switchLevels(level);
                            fmt::print("Pressed");
                        }
                    break;
                    case 1:
                        if (bat->isDead && magician1->isDead && nightBorn->isDead && this->sfmlEvent.key.code == sf::Keyboard::M) {
                            this->level++;
                            backgroundTexture = sf::Texture();
                            backgroundSprite = sf::Sprite();
                            switchLevels(level);
                            fmt::println("Pressed");
                        }
                    break;
                    case 2:
                        if (boss->isDead && this->sfmlEvent.key.code == sf::Keyboard::M){
                            this->level++;
                            backgroundTexture = sf::Texture();
                            backgroundSprite = sf::Sprite();
                            switchLevels(level);
                            fmt::println("Pressed");
                        }
                    break;
                    case 3:
                        if (this->sfmlEvent.key.code == sf::Keyboard::M){
                            this->level++;
                            backgroundTexture = sf::Texture();
                            backgroundSprite = sf::Sprite();
                            switchLevels(level);
                            fmt::println("Pressed");
                        }
                    break;
                }
            break;
        }
    }
}
void Game::switchLevels(int level) {
    if (level == 4)
        this->window->close();

    auto vecOfBackground = std::vector<std::string>{"../BackgroundImages/1.png",
                                                    "../BackgroundImages/2.png",
                                                    "../BackgroundImages/3.png",
                                                    "../BackgroundImages/4_1.png"
    };
    auto vecOfLevels = std::vector<std::string>{"../LevelNumber/1.png",
                                                "../LevelNumber/2.png",
                                                "../LevelNumber/3.png"
    };
    if (level == 3) {
        if (backgroundTexture.loadFromFile(vecOfBackground[level])) {
            backgroundSprite.setTexture(backgroundTexture);
        } else {
            fmt::println("Failed to load background texture!");
        }
        gameNameSprite = sf::Sprite();
        gameNameTexture = sf::Texture();
        return;
    }
    if (level == 2) {
        if (!bossLevelTexture.loadFromFile("../LevelNumber/3Boss.png")) {
            fmt::println("Failed to load boss level texture!");
        }
        bossLevelSprite.setTexture(bossLevelTexture);
        bossLevelSprite.setPosition(535.f, 127.f);
        bossLevelSprite.setScale(0.8f, 0.8f);

    }
    if (level >= 0 && level < vecOfBackground.size() ) {
        if (backgroundTexture.loadFromFile(vecOfBackground[level])) {
            backgroundSprite.setTexture(backgroundTexture);
        } else {
            fmt::println("Failed to load background texture!");
        }
        //levels
        if (level == 1){
            if (gameNameTexture.loadFromFile(vecOfLevels[level])) {
                gameNameSprite.setTexture(gameNameTexture);
                gameNameSprite.setPosition(window->getSize().x / 3.8f, 0);
            } else {
                fmt::println("Failed to load game name texture!");
            }
        } else if (level > 1 && level < vecOfLevels.size() || level == 0 ) {
            if (gameNameTexture.loadFromFile(vecOfLevels[level])) {
                gameNameSprite.setTexture(gameNameTexture);
                gameNameSprite.setPosition(window->getSize().x / 3.8f, 30);
            } else {
                fmt::println("Failed to load game name texture!");
            }
        }
        //reseting player to the start
        this->player = Player(sf::Vector2u(1280, 720), -70.f, 320.f);

        //Creating enemies for the levels
        switch (level) {
            case 0:
                wizard = new Wizard(sf::Vector2u(1280, 720), 1270.f, 224.f);
                magician = new Magician(sf::Vector2u(1280, 720), 1220.f, 160.f);
                loadObstacles();
                loadItems();
                break;
            case 1:
                bat = new Bat(sf::Vector2u(1280, 720), 1000.f, 250.f);
                magician1 = new Magician(sf::Vector2u(1280, 720), 1200.f, 180.f);
                nightBorn = new NightBorn(sf::Vector2u(1280, 720), 1200.f, 434.f);
                loadObstacles();
                loadItems();
                break;
            case 2:
                boss = new Boss(sf::Vector2u(1280, 720), 1500.f, 240.f);
                loadObstacles();
                loadItems();
                break;
        }
    } else {
        fmt::println("Invalid level index!");
    }
}
void Game::printHearts() {
    //for printing the hp
    auto howMuch = int();
    if (player.hp >= 175) {
        howMuch = 10;
    } else if (player.hp >= 160) {
        howMuch = 9;
    } else if (player.hp >= 145) {
        howMuch = 8;
    } else if (player.hp >= 130) {
        howMuch = 7;
    } else if (player.hp >= 115) {
        howMuch = 6;
    } else if (player.hp >= 100) {
        howMuch = 5;
    } else if (player.hp >= 80) {
        howMuch = 4;
    } else if (player.hp >= 60) {
        howMuch = 3;
    } else if (player.hp >= 40) {
        howMuch = 2;
    } else if (player.hp > 0) {
        howMuch = 1;
    } else {
        howMuch = 0;
    }
    for (int i = 0; i < howMuch; i++) {
        hpSprite.setPosition(i * 42.f, 11.f);
        hpSprite.setScale(0.4f, 0.4f);
        this->window->draw(hpSprite);
    }
}

void Game::update(float dt) {
    this->pollEvents();
    sf::Vector2f playerPosition = player.getPosition();

    if (displayItemPickupMessage && itemPickupClock.getElapsedTime().asSeconds() > 1.5f) {
        displayItemPickupMessage = false;
        hasItemBeenPickedUp = false;
        hpIncreasedFlag = false;
        speedIncreasedFlag = false;
        powerIncreasedFlag = false;
    }

    //to do animations
    this->player.update(this->wizard,
                        this->bat,
                        this->magician,
                        this->magician1,
                        this->nightBorn,
                        this->boss,
                        this,
                        dt);
    switch (level) {
        case 0:
            this->wizard->update(player, dt);
            this->magician->update(player, dt);
        break;
        case 1:
            this->bat->update(player, dt);
            this->magician1->update(player, dt);
            this->nightBorn->update(player, dt);
        break;
        case 2:
            this->boss->update(player, dt);
        break;

    }

    // Check collision with obstacle
    for (auto& obstacle : obstacles) {
        if (obstacle.checkCollision(&player)) {
            player.returnBack();
        }
    }

    //items
    for (int i = 0; i < items.size(); ++i) {
        if (items[i].checkCollision(&player)) {
            player.actionWithItems(items[i]);
            displayItemPickupMessage = true;
            if (!hasItemBeenPickedUp) {
                itemPickupClock.restart();
                hasItemBeenPickedUp = true;
            }
            if (items[i].getType() == ItemType::Medicine) {
                hpIncreasedFlag = true;
            } else if (items[i].getType() == ItemType::Speed) {
                speedIncreasedFlag = true;
            } else if (items[i].getType() == ItemType::Power) {
                powerIncreasedFlag = true;
            }
            items.erase(items.begin() + i); //removes
            --i;
        }
    }

    // Update playerCenter to the current player position
    this->playerCenter = sf::Vector2f(this->player.sprite.getPosition());

    // Clamp the center position to within the valid range
    float viewCenterX = std::max(window->getSize().x / 2.0f, std::min(backgroundTexture.getSize().x - window->getSize().x / 2.0f, playerCenter.x));
    float viewCenterY = std::max(window->getSize().y / 2.0f + 50.0f, std::min(backgroundTexture.getSize().y - window->getSize().y / 2.0f, playerCenter.y));
    this->view.setCenter(viewCenterX, viewCenterY);
}

//rendering game
void Game::render() {
    if (player.getHP() <= 0) {
        this->window->clear();
        this->window->draw(gameOverText);
        this->window->draw(toMenuText);
        this->window->display();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        this->window->close();
    }
    this->window->clear();

    // Render the background before anything else
    this->window->draw(this->backgroundSprite);
    if (level == 2)
        this->window->draw(this->bossLevelSprite);

    //render player
    if (level == 0 || level == 1 || level == 2) {
        this->player.render(this->window);
        printHearts();
    }

    //draw all
    this->window->draw(gameNameSprite);
    if (level == 0) {
        for (auto &obstacle: obstacles)
            obstacle.render(this->window);

        for (auto &item : items)
            item.render(this->window);

        if (wizard->isDead && magician->isDead){
            this->window->draw(nextLevelText);
        }
    }
    if (level == 1) {
        for (auto &obstacle: obstacles)
            obstacle.render(this->window);

        for (auto &item : items)
            item.render(this->window);
        if ( nightBorn->isDead && bat->isDead && magician1->isDead){
            this->window->draw(nextLevelText);
        }
    }
    if (level == 2) {
        for (auto &obstacle: obstacles)
            obstacle.render(this->window);

        for (auto &item : items)
            item.render(this->window);
        if (boss->isDead) {
            nextLevelText.setPosition(
                    this->window->getSize().x / 2 ,
                    this->window->getSize().y / 2 + nextLevelText.getLocalBounds().height - 142.f
                    );
            this->window->draw(nextLevelText);
        }
    }

    switch(this->level) {
        case 0:
            this->wizard->render(*this->window);
            this->magician->render(*this->window);
            break;
        case 1:
            this->bat->render(*this->window);
            this->magician1->render(*this->window);
            this->nightBorn->render(*this->window);
            break;
        case 2:
            this->boss->render(*this->window);
            break;
    }

    if (displayItemPickupMessage) {
        if (hpIncreasedText.getString() == "HP Increased!" && hpIncreasedFlag) {
            this->window->draw(hpIncreasedText);
        } else if (speedIncreasedText.getString() == "Speed Increased!" && speedIncreasedFlag) {
            this->window->draw(speedIncreasedText);
        } else if (powerOfAttackIncreasedText.getString() == "Power Increased!" && powerIncreasedFlag) {
            this->window->draw(powerOfAttackIncreasedText);
        }
    }
    this->window->display();
}

void Game::loadObstacles() {
    auto vecOfObstacles = std::vector<std::string>{
            "../Textures/rocks/Rock1.png", //0
            "../Textures/rocks/Rock2.png", //1
            "../Textures/rocks/Rock3.png", //2
            "../Textures/rocks/Rock4.png", //3

            "../Textures/crystals/crystalPurple1.png",  //4
            "../Textures/crystals/crystalPink2.png",    //5
            "../Textures/crystals/crystalBlue3.png",    //6
            "../Textures/crystals/crystal4Green.png",   //7

            "../Textures/bones/bones1.png",         //8
            "../Textures/bones/bones1Flipped.png",  //9
    };
    // Clear old obstacles and textures
    obstacles.clear();
    obstacleTextures.clear();
    for (int i = 0; i < vecOfObstacles.size(); i++) {
        obstacleTextures.emplace_back();
        if (!obstacleTextures.back().loadFromFile(vecOfObstacles[i])) {
            fmt::println("Failed to load obstacle texture...");
            return;
        }
    }

    srand(time(0));
    int randomValueBetweenOneTwo = (rand() % 2) + 1;
    int randomValueBetweenCrystals = (rand() % 6) + 1;
    int randomValueBetweenTextures = (rand() % 4) + 1;
    switch (this->level) {
        case 0:
            if (randomValueBetweenOneTwo == 1){
            //rocks
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 60.f, 250.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 1100.f, 250.f, 2.f, 2.f));

                obstacles.push_back(Obstacles(obstacleTextures[9], 60.f, 540.f, 3.f, 3.f));
                obstacles.push_back(Obstacles(obstacleTextures[8], 1150.f, 540.f, 3.f, 3.f));
            } else {
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 60.f, 250.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 60.f, 500.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 590.f, 365.f, 1.8f, 1.8f));

                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 1100.f, 250.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenOneTwo], 1100.f, 500.f, 2.f, 2.f));
            }
        break;
        case 1:
            if (randomValueBetweenOneTwo == 1) {
                //crystals
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 60.f, 250.f, 2.f, 2.3f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 1100.f, 250.f, 2.f, 2.3f));
                //bones
                obstacles.push_back(Obstacles(obstacleTextures[8], 1170.f, 500.f, 3.f, 3.3f)); //right
                obstacles.push_back(Obstacles(obstacleTextures[9], 50.f, 500.f, 3.f, 3.3f)); //left
            } else {
                //crystals
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 60.f, 250.f, 2.f, 2.3f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 590.f, 365.f, 1.8f, 2.2f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 1100.f, 250.f, 2.f, 2.3f));

                //bones
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 1130.f, 480.f, 2.f, 2.3f)); //right
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenCrystals], 50.f, 480.f, 2.f, 2.3f)); //left
            }
        break;
        case 2:
            if (randomValueBetweenOneTwo == 1) {
                //rocks
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 60.f, 250.f, 2.0f, 2.0f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 1100.f, 250.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 587.f, 520.f, 2.f, 2.f));
                //bones
                obstacles.push_back(Obstacles(obstacleTextures[8], 1140.f, 520.f, 3.f, 3.3f)); //right
                obstacles.push_back(Obstacles(obstacleTextures[9], 50.f, 520.f, 3.f, 3.3f)); //left
            } else {
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 60.f, 250.f, 2.0f, 2.0f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 1100.f, 250.f, 2.f, 2.f));
                obstacles.push_back(Obstacles(obstacleTextures[randomValueBetweenTextures], 587.f, 510.f, 2.f, 2.f));
                //bones
                obstacles.push_back(Obstacles(obstacleTextures[8], 1140.f, 520.f, 3.f, 3.3f)); //right
                obstacles.push_back(Obstacles(obstacleTextures[9], 50.f, 520.f, 3.f, 3.3f)); //left
            }
        break;
    }
}
void Game::loadItems() {
    auto vecOfItems = std::vector<std::string>{
            "../Textures/items/heart/sacredMedicine.png", //medicine [0]
            "../Textures/items/speed/Item__49.png",       //speed [1]
            "../Textures/items/sword/power.png"           //power [2]
    };

    auto intToItemType = std::vector<ItemType>{
            ItemType::Medicine,
            ItemType::Speed,
            ItemType::Power
    };

    // Clear old items and textures
    items.clear();
    itemsTextures.clear();
    for (int i = 0; i < vecOfItems.size(); i++) {
        itemsTextures.emplace_back();
        if (!itemsTextures.back().loadFromFile(vecOfItems[i])) {
            fmt::println("Failed to load item texture...");
            return;
        }
    }

    srand(time(0));
    int randomValueBetweenOneTwo = (rand() % 2) + 1;
    int randomBetweenItemOne = rand() % 3;
    int randomBetweenItemTwo = rand() % 3;
    int randomBetweenItemThird = rand() % 3;

    switch (this->level) {
        case 0:
            if (randomValueBetweenOneTwo == 1){
                items.push_back(Items(itemsTextures[randomBetweenItemOne], 780.f, 400.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[randomBetweenItemTwo], 500.f, 400.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemTwo]);

                items.push_back(Items(itemsTextures[randomBetweenItemThird], 1070.f, 570.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemThird]);
            } else {
                items.push_back(Items(itemsTextures[randomBetweenItemOne], 780.f, 400.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[randomBetweenItemThird], 200.f, 570.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemThird]);
            }
        break;
        case 1:
            if (randomValueBetweenOneTwo == 1){
                items.push_back(Items(itemsTextures[randomBetweenItemOne], 780.f, 400.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[randomBetweenItemTwo], 310.f, 400.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemTwo]);
            } else {
                items.push_back(Items(itemsTextures[randomBetweenItemOne], 780.f, 420.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[randomBetweenItemThird], 200.f, 540.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemThird]);
            }
        break;
        case 2:
            if (randomValueBetweenOneTwo == 1){
                items.push_back(Items(itemsTextures[0], 780.f, 550.f, 2.f, 2.f));
                items.back().setType(intToItemType[0]);

                items.push_back(Items(itemsTextures[0], 500.f, 550.f, 2.f, 2.f));
                items.back().setType(intToItemType[0]);

                items.push_back(Items(itemsTextures[randomBetweenItemOne], 250.f, 295.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[randomBetweenItemTwo], 1050.f, 295.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemTwo]);

            } else {
                items.push_back(Items(itemsTextures[randomBetweenItemThird], 780.f, 550.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemThird]);

                items.push_back(Items(itemsTextures[randomBetweenItemOne], 500.f, 550.f, 2.f, 2.f));
                items.back().setType(intToItemType[randomBetweenItemOne]);

                items.push_back(Items(itemsTextures[0], 250.f, 295.f, 2.f, 2.f));
                items.back().setType(intToItemType[0]);

                items.push_back(Items(itemsTextures[0], 1050.f, 295.f, 2.f, 2.f));
                items.back().setType(intToItemType[0]);
            }
        break;
    }
}