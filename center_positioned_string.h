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

    void setBackground(sf::Color color) {
        background_color_ = color;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        sf::Text val;
        val.setFont(font);
        val.setFillColor(background_color_);
        val.setCharacterSize(letter_size);
        val.setString(data_);
        val.setPosition(pos_.x - val.getLocalBounds().width / 2, pos_.y - letter_size / 1.75);

//        sf::RectangleShape bound_box(val.getLocalBounds().getSize());
//        bound_box.setPosition(pos_.x - val.getLocalBounds().width / 2,
//                              pos_.y - val.getLocalBounds().height / 2);
//        bound_box.setFillColor(background_color_);
//        target.draw(bound_box);
        target.draw(val);
    }
 private:
    sf::Color background_color_ = text_color;
    std::string data_;
    sf::Vector2f pos_ = { 0, 0 };
};