#pragma once
#include <SFML/Graphics.hpp>

class Animation {
private:
    // Private variables
    sf::Vector2u imageCount;
    sf::Vector2u currentImage; // (x, y)

    float totalTime;
    float switchTime;

public:
    // Variables
    sf::IntRect uvRect; // rectangle actual (frame actual)

    // CONSTRUCTOR & DESTRUCTOR
    // imageCount: cantidad de imagenes (columnas y filas del spritesheet).
    // switchTime:tiempo que dura cada frame antes de cambiar.
    Animation(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime);
    ~Animation();

    // Functions
    void update(int row, float deltaTime, bool faceRight, int frameCount = 0);

};