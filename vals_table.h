#include "SFML/Graphics.hpp"

#include "variable_combination.h"
#include "rounded_rectangle.h"
#include "center_positioned_string.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <set>

class ValuesTable : public sf::Drawable {
 public:
    static sf::Vector2f value_size_;
    static constexpr float net_thickness_ = 3.f;

    ValuesTable(int vars_amount, uint64_t f_ind);

    void SetSize(sf::Vector2f size);

    void SetPosition(sf::Vector2f pos);

    void MoveX(float dist);

    void MoveY(float dist);

    std::optional<std::string> NextStepMinimizing();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    sf::Vector2f size_, pos_, cur_pos_;
    uint64_t variables_amount_, function_number_, cur_column_ = 0;
    std::vector<VariablesCombination> vals_;
    std::vector<std::vector<sf::Color>> colors_;

    static sf::Color GetRandomColor();

    static std::vector<VariablesCombination> CalcAllCombinations(int var, int vars_amount);

    [[nodiscard]] sf::Vector2f GetFullSize() const;

    void FillSameInColumn(int column, std::string val, sf::Color color);

    void RemoveNextAtFunc0();

    struct Variant {
        VariablesCombination comb;
        std::string consist;

        Variant(VariablesCombination com, std::string con);

        bool operator<(const Variant &other) const;
    };

    std::string Reduce();


    static std::vector<std::vector<Variant>> CalcAllCombinationsOfVariants(std::map<Variant, std::set<int>>::const_iterator cur, const std::map<Variant, std::set<int>> &variants);

    void FillLineWithSubstr(int line, int from, const std::string &origin, sf::Color color);

    void Absorption();
};