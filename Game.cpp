#include "Game.h"

// Window
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Animation test", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initPLayer() {
    this->player = new Player();
}

void Game::initPlatform() {
    this->platform.setSize(sf::Vector2f(800.f, 50.f));
    this->platform.setFillColor(sf::Color::Red);
    this->platform.setPosition(0.f, 550.f);
}

// Constructor & destructor
Game::Game() {
    this->initWindow();
    this->initPLayer();
    this->initPlatform();
}

Game::~Game() {
    delete this->window;
    delete this->player;
}

// Functions
void Game::updatePollEvents() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed) this->window->close();
    }
}

void Game::updateInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->move(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->move(1.f, 0.f);
    }
    else{
        this->player->move(0.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->player->jump();
    }
}

void Game::updateCollsion() {
    if (this->player->getGlobalBounds().intersects(this->platform.getGlobalBounds())) {

        if (this->player->getPosition().y < this->platform.getPosition().y) {

            // detener caida.
            this->player->resetVelocityY();

            // reparar posición.
            this->player->setPosition(
                this->player->getPosition().x,
                this->platform.getPosition().y - this->player->getGlobalBounds().height
            );

            this->player->setOnGround(true);
        }
    } else {
        // si no esta tocando alguna plataforma, entonces esta en el piso.
        this->player->setOnGround(false);
    }
}

void Game::update() {
    this->updatePollEvents();
    this->updateInput();
    this->player->update(dtTime);
    this->updateCollsion();
}

void Game::runGame() {
    while (this->window->isOpen()) {
        this->dtTime = clock.restart().asSeconds();
        this->update();
        this->render();
    }
}

void Game::render() {
    this->window->clear(sf::Color(20,20,20));

    this->player->render(*this->window);

    this->window->display();
}

