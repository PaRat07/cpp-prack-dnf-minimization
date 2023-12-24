#include <iostream>
#include "button.h"

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RoundedRectangleShape rect(size_);
    rect.setPosition(pos_);
    rect.setOutlineColor(outline_color);
    rect.setFillColor(fill_color);
    rect.setPosition(pos_);
    rect.setRoundRadius(15.f);
    target.draw(rect);

    sf::Text text;
    text.setString(text_);
    text.setFont(font);
    text.setCharacterSize(letter_size);
    text.setPosition(pos_.x + size_.x / 2 - text.getLocalBounds().width / 2, pos_.y + size_.y / 2 - text.getLocalBounds().height);
    target.draw(text);
}

void Button::Click(sf::Vector2f pos) const {
    if (std::abs(pos.x - (pos_.x + size_.x / 2)) <= size_.x / 2 && std::abs(pos.y - (pos_.y + size_.y / 2)) <= size_.y / 2) {
        callback_();
    }
}

Button::Button(sf::Vector2f pos, sf::Vector2f sz, std::string text, const std::function<void()> &cb)
        : callback_(cb)
        , size_(sz)
        , pos_(pos)
        , text_(std::move(text))
{}
