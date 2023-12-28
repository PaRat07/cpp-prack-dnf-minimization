#pragma once

#include "SFML/Graphics.hpp"

sf::Font LoadFont(std::string path);

const sf::Color background_color = sf::Color(152, 147, 218);
const sf::Color text_color = sf::Color(0, 0, 0);
const sf::Color outline_color = sf::Color(114, 114, 126);
const sf::Color fill_color = sf::Color(187, 189, 246);
const sf::Font font = LoadFont("../../SpaceMono-Regular.ttf");
constexpr float letter_size = 20.f;