#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
private:
    // Window
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock clock;
    float dtTime;

    // Player
    Player* player;

    // Private functions
    void initWindow();
    void initPLayer();

public:
    // Constructor & destructor
    Game();
    ~Game();

    // Functions
    void updatePollEvents();
    void update();
    void runGame();
    void render();
};