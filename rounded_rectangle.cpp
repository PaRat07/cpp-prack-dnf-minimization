#include "rounded_rectangle.h"

sf::RoundedRectangleShape::RoundedRectangleShape(sf::Vector2f size)
        : size_(size)
{
}

void sf::RoundedRectangleShape::setSize(sf::Vector2f new_size) {
    size_ = new_size;
}

void sf::RoundedRectangleShape::setPosition(sf::Vector2f new_pos) {
    pos_ = new_pos;
}

void sf::RoundedRectangleShape::setFillColor(sf::Color new_color) {
    if (new_color == sf::Color::Transparent) throw std::runtime_error("RoundedRectangleShape doesn't support transparent fill color");
    fill_color_ = new_color;
}

void sf::RoundedRectangleShape::setOutlineColor(sf::Color new_color) {
    outline_color_ = new_color;
}

void sf::RoundedRectangleShape::setOutlineThickness(float thick) {
    outline_thickness_ = thick;
}

void sf::RoundedRectangleShape::setRoundRadius(float new_r) {
    radius_ = new_r;
}
