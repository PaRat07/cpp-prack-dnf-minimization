#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace sf {

 class RoundedRectangleShape : public sf::Drawable {
 public:
    RoundedRectangleShape(sf::Vector2f size);

    void setSize(sf::Vector2f new_size);

    const sf::Vector2f &getSize() const { return size_; }

    void setPosition(sf::Vector2f new_pos);

    const sf::Vector2f &getPosition() const { return pos_; }

    void setFillColor(sf::Color new_color);

    void setOutlineColor(sf::Color new_color);

    const sf::Color &getFillColor() const {
        return fill_color_;
    }

    const sf::Color &getOulineColor() const {
        return outline_color_;
    }

    void setOutlineThickness(float thick);

    const float &getOutlineThickness() const {
        return outline_thickness_;
    }

    void setRoundRadius(float new_r);

    const float &getRoundRadius() const { return radius_; }

    void draw(RenderTarget& target, RenderStates states) const override {
        sf::CircleShape lu, ld, ru, rd;

        lu.setPointCount(50);
        ld.setPointCount(50);
        ru.setPointCount(50);
        rd.setPointCount(50);

        lu.setRadius(radius_);
        ld.setRadius(radius_);
        ru.setRadius(radius_);
        rd.setRadius(radius_);

        lu.setPosition(pos_.x + outline_thickness_, pos_.y + outline_thickness_);
        ld.setPosition(pos_.x + outline_thickness_, pos_.y + size_.y - radius_ * 2 - outline_thickness_);
        ru.setPosition(pos_.x + size_.x - radius_ * 2 - outline_thickness_, pos_.y + outline_thickness_);
        rd.setPosition(pos_.x + size_.x - radius_ * 2 - outline_thickness_, pos_.y + size_.y - radius_ * 2 - outline_thickness_);

        lu.setOutlineColor(outline_color_);
        ld.setOutlineColor(outline_color_);
        ru.setOutlineColor(outline_color_);
        rd.setOutlineColor(outline_color_);

        lu.setOutlineThickness(outline_thickness_);
        ld.setOutlineThickness(outline_thickness_);
        ru.setOutlineThickness(outline_thickness_);
        rd.setOutlineThickness(outline_thickness_);

        lu.setFillColor(fill_color_);
        ld.setFillColor(fill_color_);
        ru.setFillColor(fill_color_);
        rd.setFillColor(fill_color_);

        target.draw(lu);
        target.draw(ld);
        target.draw(ru);
        target.draw(rd);

        sf::RectangleShape horizontal(sf::Vector2f(size_.x - outline_thickness_ * 2, size_.y - radius_ * 2 - outline_thickness_ * 2));
        horizontal.setPosition(pos_.x + outline_thickness_, pos_.y + radius_ + outline_thickness_);
        horizontal.setFillColor(fill_color_);
        target.draw(horizontal);

        sf::RectangleShape vertical(sf::Vector2f(size_.x - radius_ * 2 - outline_thickness_ * 2, size_.y - outline_thickness_ * 2));
        vertical.setPosition(pos_.x + radius_ + outline_thickness_, pos_.y + outline_thickness_);
        vertical.setFillColor(fill_color_);
        target.draw(vertical);

        sf::RectangleShape u(sf::Vector2f(size_.x - radius_ * 2, outline_thickness_));
        u.setFillColor(outline_color_);
        u.setPosition(pos_.x + radius_, pos_.y);
        target.draw(u);

        sf::RectangleShape d(sf::Vector2f(size_.x - radius_ * 2, outline_thickness_));
        d.setFillColor(outline_color_);
        d.setPosition(pos_.x + radius_, pos_.y + size_.y - outline_thickness_);
        target.draw(d);

        sf::RectangleShape l(sf::Vector2f(outline_thickness_, size_.y - radius_ * 2));
        l.setFillColor(outline_color_);
        l.setPosition(pos_.x, pos_.y + radius_);
        target.draw(l);

        sf::RectangleShape r(sf::Vector2f(outline_thickness_, size_.y - radius_ * 2));
        r.setFillColor(outline_color_);
        r.setPosition(pos_.x + size_.x - outline_thickness_, pos_.y + radius_);
        target.draw(r);
    }

 private:
    float radius_ = 0, outline_thickness_ = 1;
    sf::Vector2f pos_{ 0.f, 0.f}, size_;
    sf::Color outline_color_ = sf::Color::Black, fill_color_ = sf::Color::Transparent;
};

} // namespace sf