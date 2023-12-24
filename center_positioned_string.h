#include "SFML/Graphics.hpp"

#include "general_data.h"

class CenterPositionedString : public sf::Drawable {
 public:

    void setPosition(float x, float y) {
        pos_ = { x, y };
    }

    void setPosition(sf::Vector2f pos) {
        pos_ = pos;
    }

    void setString(std::string s) {
        data_ = std::move(s);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        sf::Text val;
        val.setFont(font);
        val.setFillColor(text_color);
        val.setCharacterSize(letter_size);
        val.setString(data_);
        val.setPosition(pos_.x - val.getLocalBounds().width / 2, pos_.y - letter_size / 1.75);
        target.draw(val);

        sf::RectangleShape bound_box(val.getLocalBounds().getSize());
        bound_box.setPosition(val.getPosition());
        bound_box.setFillColor(sf::Color::Transparent);
        bound_box.setOutlineThickness(3);
        bound_box.setOutlineColor(sf::Color::Black);
#ifdef DEBUG
        target.draw(bound_box);
#endif
    }
 private:
    std::string data_;
    sf::Vector2f pos_ = { 0, 0 };
};