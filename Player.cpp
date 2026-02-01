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
    this->sprite.setScale(2.f, 2.f);
}

void Player::initAnimation() {
    // el spriteSheet tiene 10 frames en horizontal y 11 en vertical
    this->animation = new Animation(&this->texture, sf::Vector2u(10, 11), 0.05f);
    this->faceRight = true;
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
        this->faceRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += this->speed * deltaTime;
        this->faceRight = true;
    }

    int currentFrames = 0; // variable para guardar cuantos frames usaremos

    // selección de animación (Row)
    if (movement.x == 0.0f) {
        this->row = 0; // IDLE
        currentFrames = 6; // Idle solo usa 6 cuadros
    } else {
        this->row = 1; // WALK
        currentFrames = 8; // correr usa 8 cuadros
    }

    // actualizar animación y aplicar al sprite
    this->animation->update(this->row, deltaTime, this->faceRight, currentFrames);

    this->sprite.setTextureRect(this->animation->uvRect);
    this->sprite.move(movement);
}

// Functions
void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

