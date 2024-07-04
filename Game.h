#pragma once

#include <ctime>
#include <memory>

#include "Obstacles.h"
#include "Items.h"
#include "Button.h"

#include "Player.h"

//enemies
#include "Wizard.h"
#include "Bat.h"
#include "Magician.h"
#include "NightBorn.h"
#include "Boss.h"

struct Game {
    int level = 0;

    //clock for text
    sf::Clock itemPickupClock;

    //text
    sf::Font font;
    sf::Text gameOverText;
    sf::Text nextLevelText;
    sf::Text toMenuText;
    sf::Text hpIncreasedText;
    sf::Text speedIncreasedText;
    sf::Text powerOfAttackIncreasedText;

    //bool
    bool showImage;
    bool endGame;

    sf::Texture hpTexture;
    sf::Sprite hpSprite;

    //window
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event sfmlEvent;
    sf::Clock clock;

    //background texture
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    //for displaying text: "boss"
    sf::Texture bossLevelTexture;
    sf::Sprite bossLevelSprite;

    //name of the game texture
    sf::Texture gameNameTexture;
    sf::Sprite gameNameSprite;

    //for player
    Player player;
    sf::Vector2f playerCenter;
    sf::View view;

    //enemies
    Wizard* wizard = nullptr;
    Bat* bat = nullptr;
    Magician* magician = nullptr;
    Magician* magician1 = nullptr;
    NightBorn* nightBorn = nullptr;
    Boss* boss = nullptr;

    //bool
    bool displayItemPickupMessage = false;
    bool speedIncreasedFlag = false;
    bool hpIncreasedFlag = false;
    bool powerIncreasedFlag = false;
    bool hasItemBeenPickedUp = false;

    //obstacles
    std::vector<Obstacles> obstacles;
    std::vector<sf::Texture> obstacleTextures;

    std::vector<Items> items;
    std::vector<sf::Texture> itemsTextures;

    //constructor and destructor
    Game();
    ~Game();

    //------------------methods
    //player hp
    void printHearts();

    //obstacles
    void loadObstacles();

    //items
    void loadItems();
    //levels
    void switchLevels(int i);

    //showing the game
    void render();
    void update(float dt);

    //other stuff
    sf::Text createText(const std::string& string, int size, const sf::Color& fillColor, const sf::Vector2f& position);
    void initWindow();
    void initVariables();
    bool running() const;
    void pollEvents();
};