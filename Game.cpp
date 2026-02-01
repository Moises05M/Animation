#include "Game.h"

// Window
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Animation test", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initPLayer() {
    this->player = new Player();
}

// Constructor & destructor
Game::Game() {
    this->initWindow();
    this->initPLayer();
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

void Game::update() {
    this->player->update(dtTime);
    this->updatePollEvents();
}

void Game::runGame() {
    while (this->window->isOpen()) {
        this->dtTime = clock.restart().asSeconds();
        this->update();
        this->render();
    }
}

void Game::render() {
    this->window->clear(sf::Color(0, 0, 0, 255));

    this->player->render(*this->window);

    this->window->display();
}

