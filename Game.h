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

    // Platform
    sf::RectangleShape platform;

    // Private functions
    void initWindow();
    void initPLayer();
    void initPlatform();

public:
    // Constructor & destructor
    Game();
    ~Game();

    // Functions
    void updatePollEvents();
    void updateInput();
    void updateCollsion();
    void update();
    void runGame();
    void render();
};