#include "Player.h"
#include <iostream>

// Private functions
void Player::initTexture() {
    if(!this->texture.loadFromFile("assets/SPRITE_SHEET.png")) {
        std::cout << "ERROR AL CARGAR LA TEXTURA!" << std::endl;
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
}

void Player::initAnimation() {
    // el spriteSheet tiene 12 frames en horizontal y 11 en vertical
    this->animation = new Animation(&this->texture, sf::Vector2u(10, 11), 0.05f);
    this->faceRight = false;
    this->row = 0;
}

void Player::initVariables() {
    this->speed = 200.f;
}

// Constructor & destructor
Player::Player() {
    this->initTexture();
    this->initSprite();
    this->initVariables();
    this->initAnimation();
}

Player::~Player() {
    delete this->animation;
}

void Player::update(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= this->speed * deltaTime;
        this->faceRight = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += this->speed * deltaTime;
        this->faceRight = false;
    }

    // selección de animación (Row)
    if (movement.x == 0.0f) {
        this->row = 0; // IDLE
    } else {
        this->row = 1; // WALK
    }

    // ctualizar animación y aplicar al sprite
    this->animation->update(this->row, deltaTime, this->faceRight);
    this->sprite.setTextureRect(this->animation->uvRect);

    this->sprite.move(movement);
}

// Functions
void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

