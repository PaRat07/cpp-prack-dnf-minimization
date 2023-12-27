#include "SFML/Graphics.hpp"

#include "value_shape.h"
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

    ValuesTable(uint64_t vars_amount, uint64_t f_ind);

    void SetSize(sf::Vector2f size);

    void SetPosition(sf::Vector2f pos);

    void MoveX(float dist);

    void MoveY(float dist);

    std::optional<std::string> NextStepMinimizing() {
        if (cur_column_ == -2) {
            return std::nullopt;
        } else if (cur_column_ == -1) {
            cur_column_ = -2;
            return Reduce();
        } else if (cur_column_ < vals_.size()) {
            RemoveNextAtFunc0();
            return std::nullopt;
        } else {
            Absorption();
            cur_column_ = -1;
            return std::nullopt;
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    sf::Vector2f size_, pos_, cur_pos_;
    uint64_t variables_amount_, function_number_, cur_column_ = 0;
    std::vector<VariablesCombination> vals_;
    std::vector<std::vector<sf::Color>> colors_;

    static sf::Color GetRandomColor() {
//        return sf::Color::Red;
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

    void RemoveNextAtFunc0() {
        for (uint64_t i = 0, func_num_copy = function_number_; i <= vals_.size(); ++i, func_num_copy >>= 1) {
            if (!(func_num_copy & 1)) {
                FillSameInColumn(cur_column_, vals_[cur_column_].GetVal(i), GetRandomColor());
            }
        }
        ++cur_column_;
    }

    struct Variant {
        VariablesCombination comb;
        std::string consist;

        Variant(VariablesCombination com, std::string con)
            : comb(std::move(com))
            , consist(std::move(con))
        {}

        bool operator<(const Variant &other) const {
            return std::pair(comb, consist) < std::pair(other.comb, other.consist);
        }
    };

    std::string Reduce() {
        std::map<Variant, std::set<int>> variants;

        for (int i = 1; i <= vals_.size(); ++i) {
            for (int j = 1; j <= (1 << variables_amount_); ++j) {
                if (colors_[i - 1][j - 1] == text_color) {
                    variants[Variant(vals_[i - 1], vals_[i - 1].GetVal(j - 1))].insert(j);
                }
            }
        }

        int amount1 = 0;
        uint64_t func_copy = function_number_;
        while (func_copy) {
            if (func_copy & 1) {
                ++amount1;
            }
            func_copy >>= 1;
        }

        auto combs = CalcAllCombinationsOfVariants(variants.begin(), variants);
        std::map<int, std::vector<std::vector<Variant>>> full_combs_for_length;
        for (const auto &i : combs) {
            std::set<int> has;
            for (const Variant &v : i) {
                has.insert(variants[v].begin(), variants[v].end());
            }
            if (has.size() == amount1) {
                full_combs_for_length[i.size()].push_back(i);
            }
        }
        std::string ans;
        for (const auto &i : full_combs_for_length.begin()->second) {
            std::string var;
            for (const auto &j : i) {
                for (int l = 0; l < j.consist.size(); ++l) {
                    var += (j.consist[l] == '1' ? j.comb.GetVars()[l].GetName() : "(!"s + j.comb.GetVars()[l].GetName() + ")"s);
                }
                var += " v ";
            }
            var.resize(var.size() - 3);
            ans += var + "\n";
        }
        return ans;
    }


    static std::vector<std::vector<Variant>> CalcAllCombinationsOfVariants(std::map<Variant, std::set<int>>::const_iterator cur, const std::map<Variant, std::set<int>> &variants) {
        if (cur == variants.end()) {
            return {};
        }

        std::vector<std::vector<Variant>> all_with_less = CalcAllCombinationsOfVariants(std::next(cur), variants);
        std::vector<std::vector<Variant>> ans;
        ans.push_back(std::vector<Variant>{ cur->first });
        std::copy(all_with_less.begin(), all_with_less.end(), std::back_inserter(ans));
        for (auto i : all_with_less) {
            i.push_back(cur->first);
            ans.push_back(i);
        }

        return ans;
    }

    void FillLineWithSubstr(int line, int from, const std::string &origin, sf::Color color) {
        if (from >= vals_.size()) return;

        int ind_origin = 0;
        for (char sym : vals_[from].GetName()) {
            if (sym == origin[ind_origin]) {
                ++ind_origin;
            }
        }
        if (ind_origin == origin.size() && colors_[from][line] == text_color) {
            colors_[from][line] = color;
        }
        FillLineWithSubstr(line, from + 1, origin, color);
    }

    void Absorption() {
        for (int i = 0; i < (1 << variables_amount_); ++i) {
            for (int j = 0; j < vals_.size(); ++j) {
                if (colors_[j][i] == text_color) {
                    FillLineWithSubstr(i, j + 1, vals_[j].GetName(), sf::Color::Red);
                }
            }
        }
    }
};