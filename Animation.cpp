
#include "Animation.h"

// CONSTRUCTOR & DESTRUCTOR
Animation::Animation(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime) {
    this->imageCount = _imageCount;
    this->switchTime = _switchTime;
    this->totalTime = 0.f;
    this->currentImage.x = 0;

    // calcular el ancho y alto del un solo Frame dividiendo el tamaño total de la textura por la cantidad
    // de cuadros indicados tanto en x, y
    this->uvRect.width = _texture->getSize().x / float(imageCount.x);
    this->uvRect.height = _texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {
}

void Animation::update(int row, float deltaTime, bool faceRight) {
    this->currentImage.y = row; // Fila donde se encuentran los frames de la animación.
    this->totalTime += deltaTime;

    // cambiar a los siguientes Frames
    if (this->totalTime >= this->switchTime) {
        this->totalTime -= this->switchTime; // reiniciar el totalTime
        this->currentImage.x++; // pasar al siguiente frame (columna)

        // verificar si ya he llegado al limite de los frames que conforman la animación para volver a empezar
        if (this->currentImage.x == this->imageCount.x) {
            this->currentImage.x = 0;
        }
    }

    // Flip
    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight) {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    } else {
        // para voltear en X, movemos el left al final del frame y hacemos el width negativo
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}
