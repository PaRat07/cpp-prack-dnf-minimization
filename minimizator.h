#include <memory>
#include <random>
#include <chrono>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "vals_table.h"
#include "inoutput_field.h"
#include "button.h"

class Minimizator {
 public:
    Minimizator();

    void Draw();

 private:
    sf::Text function_number_, variables_amount_, ans_;
    InOutputField func_num_, vars_amount_;
    Button but_;
    sf::RenderWindow win_;
    std::unique_ptr<ValuesTable> data_;

    void Render();
};