#pragma once

#include "SFML/Graphics.hpp"

#include "general_data.h"


class ValueShape : public sf::Drawable {
 public:
    ValueShape(sf::Vector2f pos, sf::Vector2f sz)
        : pos_(pos)
        , sz_(sz)
    {
    }

     void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        sf::Text text;
        text.setString(val_);
        text.setCharacterSize(letter_size);
        text.setFont(font);
        text.setFillColor(text_color);
        target.draw(text);
        sf::RectangleShape rect(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));
        rect.setPosition(pos_);
        target.draw(rect);
    }

    void SetOutboxColor(sf::Color outbox_color) {
        outbox_color_ = outbox_color;
    }

    std::string &GetVal() {
        return val_;
    }
 private:
    sf::Vector2f pos_, sz_;
    sf::Color outbox_color_ = sf::Color::Transparent;
    std::string val_;
};