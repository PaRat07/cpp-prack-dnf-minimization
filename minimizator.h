#include <memory>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "vals_table.h"

class Minimizator {
 public:
    Minimizator()
        : win_(sf::VideoMode(800, 600), "Minimizator")
    {
        uint64_t amount_of_vars = 6, number_of_func = 1;
//        std::cin >> amount_of_vars >> number_of_func;
//        std::tie(amount_of_vars, number_of_func) = GetInput();

        data_ = std::make_unique<ValuesTable>(amount_of_vars, number_of_func);
        data_->SetSize(sf::Vector2f(600, 400));
        data_->SetPosition(sf::Vector2f(10, 10));
        win_.clear(background_color);
        win_.draw(*data_);
        win_.display();
        while (win_.isOpen()) {
            sf::Event event{};
            while (win_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    win_.close();
                } else if (event.type == sf::Event::MouseWheelMoved) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        data_->MoveX(event.mouseWheel.delta);
                    } else {
                        data_->MoveY(event.mouseWheel.delta);
                    }
                    win_.clear(background_color);
                    win_.draw(*data_);
                    win_.display();
                }
            }
        }
    }
 private:
    sf::RenderWindow win_;
    std::unique_ptr<ValuesTable> data_;
    std::pair<int, int> GetInput();

    void Remove(std::string val, int column);
    void Remove(sf::Vector2i pos);
};