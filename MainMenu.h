#pragma once
#include "Button.h"

struct MainMenu {
    //bool
    bool showImage;
    bool endGame;

    //buttons
    Button* button1;
    Button* button2;
    Button* button3;
    Button* button4;
    //pressed
    Button* button3Pressed;
    Button* button2Pressed;
    //to show the content inside buttons
    Button* button3Content;
    Button* button2Content;

    //window
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event sfmlEvent;

    //background
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    //name of the game
    sf::Texture nameGameTexture;
    sf::Sprite nameGameSprite;

    //constr and destr
    MainMenu();
    ~MainMenu();

    //methods
    void initWindow();
    void initVariables();
    bool running() const;
    void pollEvents();
    void render();
    void handleButtonClick();
    void update(float dt);

};