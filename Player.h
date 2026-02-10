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
    sf::Vector2f movement;
    float speed;
    float gravity;
    float jumpHeight;

    float acceleration;
    float drag;
    float maxSpeed;
    bool isOnFloor;

    // Private functions
    void initTexture();
    void initSprite();
    void initAnimation();
    void initVariables();

public:
    // Constructor & destructor
    Player();
    ~Player();

    // Accessor
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getPosition() const;

    // Modifier
    void resetVelocityY();
    void setPosition(const float x, const float y);
    void setOnGround(bool onFloor);

    // Functions
    void move(const float dir_x, const float dir_y);
    void jump();
    void updatePhysics(float& deltaTime);
    void updateAnimation(float& deltaTime);
    void update(float &delta);
    void render(sf::RenderTarget& target);
};