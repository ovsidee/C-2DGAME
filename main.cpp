#include "MainMenu.h"

auto main() -> int {
    // Initialize MainMenu
    MainMenu mainMenu;
    sf::Clock clock;

    //menu Loop
    while (mainMenu.running()) {
        sf::Time elapsed = clock.restart();
        mainMenu.update(elapsed.asSeconds());
        mainMenu.render();
    }

    return 0;
}