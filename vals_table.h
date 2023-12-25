#include "SFML/Graphics.hpp"

#include "value_shape.h"
#include "variable_combination.h"
#include "rounded_rectangle.h"
#include "center_positioned_string.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <random>

class ValuesTable : public sf::Drawable {
 public:
    static sf::Vector2f value_size_;
    static constexpr float net_thickness_ = 3.f;

    ValuesTable(uint64_t vars_amount, uint64_t f_ind);

    void SetSize(sf::Vector2f size);

    void SetPosition(sf::Vector2f pos);

    void MoveX(float dist);

    void MoveY(float dist);

    void RemoveNextAtFunc0() {
        for (uint64_t i = 1, func_num_copy = function_number_; i < vals_.size(); ++i, func_num_copy >>= 1) {
            if (!(func_num_copy & 1)) {
                FillSameInColumn(cur_column_, vals_[cur_column_].GetVal(i), GetRandomColor());
            }
        }
        ++cur_column_;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    sf::Vector2f size_, pos_, cur_pos_;
    uint64_t variables_amount_, function_number_, cur_column_ = 0;
    std::vector<VariablesCombination> vals_;
    std::vector<std::vector<sf::Color>> colors_;

    static sf::Color GetRandomColor() {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        uint32_t rand_num = gen();
        uint8_t r = 0;
        for (int i = 1; i < 8; ++i) {
            r |= rand_num & (1 << i);
        }
        uint8_t g = 0;
        for (int i = 8; i < 16; ++i) {
            g |= (rand_num & (1 << i)) >> 8;
        }
        uint8_t b = 0;
        for (int i = 16; i < 24; ++i) {
            g |= (rand_num & (1 << i)) >> 16;
        }
        return { r, g, b };
    }

    static std::vector<VariablesCombination> CalcAllCombinations(int var, int vars_amount);

    sf::Vector2f GetFullSize() const;

    void FillSameInColumn(int column, std::string val, sf::Color color);
};