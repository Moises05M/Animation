#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player {
private:
    // Private variables
    sf::Texture texture;
    sf::Sprite sprite;
    Animation* animation;

    unsigned int row; // fila actual de la animación (0=Idle, 1=Walk)
    bool faceRight;

    // Physics
    float speed;

    // Private functions
    void initTexture();
    void initSprite();
    void initAnimation();
    void initVariables();

public:
    // Constructor & destructor
    Player();
    ~Player();

    // Functions
    void update(float delta);
    void render(sf::RenderTarget& target);
};