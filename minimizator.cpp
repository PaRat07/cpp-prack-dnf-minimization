#include "minimizator.h"

Minimizator::Minimizator()
        : win_(sf::VideoMode(940, 650), "Minimizator", sf::Style::Titlebar | sf::Style::Close)
        , function_number_("Function number", font, letter_size)
        , variables_amount_("Variables amount", font, letter_size)
        , func_num_(sf::Vector2f(620, 40), sf::Vector2f(300, 40))
        , vars_amount_(sf::Vector2f(620, 120), sf::Vector2f(300, 40))
        , ans_("", font, letter_size)
        , but_(sf::Vector2f(620, 170), sf::Vector2f(300, 240), "../../zhdun.png", [&]() { Draw(); })
{
    ans_.setFillColor(text_color);
    function_number_.setFillColor(text_color);
    variables_amount_.setFillColor(text_color);

    ans_.setPosition(10, 420);
    function_number_.setPosition(620, 10);
    variables_amount_.setPosition(620, 90);

    data_ = std::make_unique<ValuesTable>(1, 1);
    data_->SetSize(sf::Vector2f(600, 400));
    data_->SetPosition(sf::Vector2f(10, 10));
    Render();
    while (win_.isOpen()) {
        sf::Event event{};
        while (win_.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::TextEntered: {
                    switch (event.text.unicode) {
                        // Esc
                        case 27: {
                            win_.close();
                            break;
                        }
                            // Enter
                        case 13: {
                            std::optional<std::string> s = data_->NextStepMinimizing();
                            if (s.has_value()) {
                                ans_.setString(*s);
                            }

                            Render();
                            break;
                        }
                        default: {
                            func_num_.Write(event.text.unicode);
                            vars_amount_.Write(event.text.unicode);
                            Render();
                            break;
                        }
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    func_num_.Click(sf::Vector2f(static_cast<float>(event.mouseButton.x),
                                                      static_cast<float>(event.mouseButton.y)));

                    vars_amount_.Click(sf::Vector2f(static_cast<float>(event.mouseButton.x),
                                                         static_cast<float>(event.mouseButton.y)));

                    but_.Click(sf::Vector2f(static_cast<float>(event.mouseButton.x),
                                                 static_cast<float>(event.mouseButton.y)));

                    Render();
                    break;
                }
                case sf::Event::MouseWheelScrolled: {
                    if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::HorizontalWheel) {
                        data_->MoveX(event.mouseWheelScroll.delta * 10);
                    } else {
                        data_->MoveY(event.mouseWheelScroll.delta);
                    }
                    Render();
                    break;
                }
                case sf::Event::Closed: {
                    win_.close();
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void Minimizator::Draw() {
    data_ = std::make_unique<ValuesTable>(std::stoll(vars_amount_.GetText()), std::stoll(func_num_.GetText()));
    data_->SetSize(sf::Vector2f(600, 400));
    data_->SetPosition(sf::Vector2f(10, 10));
}

void Minimizator::Render() {
    win_.clear(background_color);
    win_.draw(function_number_);
    win_.draw(variables_amount_);
    win_.draw(func_num_);
    win_.draw(vars_amount_);
    win_.draw(*data_);
    win_.draw(but_);
    win_.draw(ans_);
    win_.display();
}
