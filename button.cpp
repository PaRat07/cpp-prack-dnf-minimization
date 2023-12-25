#include <cassert>
#include "button.h"

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RoundedRectangleShape rect(size_);
    rect.setPosition(pos_);
    rect.setOutlineColor(outline_color);
    rect.setFillColor(fill_color);
    rect.setPosition(pos_);
    rect.setRoundRadius(15.f);
    target.draw(rect);


    sf::Texture texture;
    assert(texture.loadFromFile(path_to_png_));
    sf::Sprite sprite(texture);
    float factor = std::min(size_.x / texture.getSize().x, size_.y / texture.getSize().y) - 0.01;
    sprite.setScale(factor, factor);
    sprite.setPosition(pos_.x + size_.x / 2 - texture.getSize().x / 2 * factor,
                       pos_.y + size_.y / 2 - texture.getSize().x / 2 * factor);
    target.draw(sprite);
}

void Button::Click(sf::Vector2f pos) const {
    if (std::abs(pos.x - (pos_.x + size_.x / 2)) <= size_.x / 2 && std::abs(pos.y - (pos_.y + size_.y / 2)) <= size_.y / 2) {
        callback_();
    }
}

Button::Button(sf::Vector2f pos, sf::Vector2f sz, std::string path, const std::function<void()> &cb)
        : callback_(cb)
        , size_(sz)
        , pos_(pos)
        , path_to_png_(std::move(path))
{}
