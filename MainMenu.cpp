#include "MainMenu.h"
#include <fmt/ranges.h>
#include "Game.h"

// Initialize Window
void MainMenu::initWindow(){
    this->videoMode = sf::VideoMode(1280, 720);
    this->window = new sf::RenderWindow(this->videoMode, "Elden Ring DLC",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

// MainMenu constructor \ destructor
MainMenu::MainMenu()
                : window(nullptr),
                button3Pressed(nullptr),
                button2Pressed(nullptr),
                button3Content(nullptr),
                button2Content(nullptr)
{
    this->initWindow();
    this->initVariables();

    //background
    if (bgTexture.loadFromFile("../BackgroundImages/1.png"))
        bgSprite.setTexture(bgTexture);
    else
        fmt::println("Failed to load background texture!");

    //name of the game
    if (nameGameTexture.loadFromFile("../BackgroundImages/NameOfTheGame2_1_59.png")){
        nameGameSprite.setTexture(nameGameTexture);
        nameGameSprite.setPosition(window->getSize().x / 4.3f, 50);
    } else fmt::println("Failed to load game name texture!");

    button1 = new Button("../Buttons/button1.png", 20.0f, 190.0f, 0.7f, 0.7f );
    button2 = new Button("../Buttons/button2.png", 420.0f, 190.0f, 0.7f, 0.7f );
    button3 = new Button("../Buttons/button3.png", 830.0f, 190.0f, 0.7f, 0.7f );
    button4 = new Button("../Buttons/exitButton.png", 1210.0f, -2.0f, 0.07f, 0.07f );
}
MainMenu::~MainMenu() {
    delete this->window;

    //to prevent memory leak
    delete button1;
    delete button2;
    delete button3;
    delete button4;
    delete button3Pressed;
    delete button2Pressed;
    delete button3Content;
    delete button2Content;
}

//methods
void MainMenu::initVariables() {
    this->endGame = false;
}
bool MainMenu::running() const {
    return this->window->isOpen();
}
void MainMenu::pollEvents(){
    while (this->window->pollEvent(this->sfmlEvent)){
        switch (this->sfmlEvent.type) {
            case sf::Event::Closed :
                this->window->close();
                break;
            case sf::Event::KeyPressed :
                if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            case sf::Event::MouseButtonReleased:
                if (sf::Mouse::Left == this->sfmlEvent.mouseButton.button) {
                    fmt::println("Mouse button hitted :3");
                    handleButtonClick();
                }
                break;
        }
    }
}

void MainMenu::handleButtonClick() {
    //button1
    if (button1->isClicked(this->window)) {
//        this->window->close();
        Game game;  // Then initialize game by passing MainMenu to it
        sf::Clock clock;

        //Game Loop
        while (game.running()) {
            sf::Time elapsed = clock.restart();
            game.update(elapsed.asSeconds() );
            game.render();
        }
        return;
    }
    //button2
    if (button2->isClicked(this->window)) {
        fmt::println("Button 2 is clicked!");
        // Toggle the new button and content when button2 is clicked
        if (button2Pressed || button2Content) {
            fmt::println("Deleting button2Pressed and button2Content");
            delete button2Pressed;
            delete button2Content;
            button2Pressed = nullptr;
            button2Content = nullptr;
        } else {
            fmt::println("Creating new button2Pressed and button2Content");
            button2Pressed = new Button("../Buttons/buttonpress2.png", 420.0f, 185.0f, 0.57f, 0.57f);
            button2Content = new Button("../Buttons/Button2Content2.png", 390.0f, 320.0f, 0.25f, 0.25f);
        }
    }
    //button3
    if (button3->isClicked(this->window)) {
        fmt::println("Button 3 is clicked!");
        // Toggle the new button and content when button3 is clicked
        if (button3Pressed || button3Content) {
            fmt::println("Deleting button3Pressed and button3Content");
            delete button3Pressed;
            delete button3Content;
            button3Pressed = nullptr;
            button3Content = nullptr;
        } else {
            fmt::println("Creating new button3Pressed and button3Content");
            button3Pressed = new Button("../Buttons/buttonpress3.png", 830.0f, 185.0f, 0.57f, 0.57f);
            button3Content = new Button("../Buttons/button3ContentUSED.png", 883.0f, 357.0f, 1.04f, 1.04f);
        }
    }
    //button4
    if (button4->isClicked(this->window)) {
        this->window->close();
    }

    // Handle interaction with the new buttons
    if (button3Pressed && button3Pressed->isClicked(this->window)) {
        fmt::println("Button3 is clicked!, Showing content of button3.");
    }
    if (button2Pressed && button2Pressed->isClicked(this->window)) {
        fmt::println("New Button2 is clicked!");
    }
}
void MainMenu::render() {
    this->window->clear();

    // Render the background before anything else
    this->window->draw(this->bgSprite);

    //render player
//    this->player.render(this->window);
    window->draw(nameGameSprite);

    //buttons
    button1->drawButton(this->window);
    button2->drawButton(this->window);
    button3->drawButton(this->window);
    button4->drawButton(this->window);

    //Draw the new button if it has been created
    if (button3Pressed) {
        button3Pressed->drawButton(this->window);
    }
    if (button2Pressed) {
        button2Pressed->drawButton(this->window);
    }
    if (button3Content) {
        button3Content->drawButton(this->window);
    }
    if (button2Content) {
        button2Content->drawButton(this->window);
    }

    this->window->display();
}
void MainMenu::update(float dt) {
    this->pollEvents();
}