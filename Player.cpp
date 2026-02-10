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
    this->movement = sf::Vector2f(0.f, 0.f);
    this->speed = 200.f;
    this->gravity = 1000.f;
    this->jumpHeight = 400.f;
    this->acceleration = 80.f;
    this->drag = 0.85f;
    this->maxSpeed = 500.f;
    this->isOnFloor = false;
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

// Accessor
const sf::FloatRect Player::getGlobalBounds() const{
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const {
    return this->sprite.getPosition();
}

// Modifier
void Player::resetVelocityY() {
    this->movement.y = 0.f;
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Player::setOnGround(bool onFloor) {
    this->isOnFloor = onFloor;
}

// Functions
void Player::move(const float dir_x, const float dir_y) {
    this->movement.x += this->acceleration * dir_x;

    // flip sprite
    if (dir_x > 0.f) {
        this->faceRight = true;
    }
    else if (dir_x < 0.f){
        this->faceRight = false;
    }

    // limitiar el movimiento a la velocidad minima
    if (std::abs(this->movement.x) > this->maxSpeed) {
        this->movement.x = this->maxSpeed * ((this->movement.x < 0.f) ? -1.f : 1.f);
    }
}

void Player::jump() {
    if (isOnFloor) {
        isOnFloor = false;
        this->movement.y = -this->jumpHeight;
    }
}

void Player::updatePhysics(float& deltaTime) {
    // aplicar gravedad
    this->movement.y += this->gravity * deltaTime;

    // fricción
    this->movement.x *= this->drag;

    // eliminar eliminar el movimiento diminuto a 0.
    if (std::abs(this->movement.x) < 1.0f) this->movement.x = 0.f;

    // movimiento
    this->sprite.move(this->movement * deltaTime);
}

void Player::updateAnimation(float &deltaTime) {
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
}

void Player::update(float& deltaTime) {
    this->updatePhysics(deltaTime);
    this->updateAnimation(deltaTime);
}

// Functions
void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}