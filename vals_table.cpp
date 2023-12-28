#include "vals_table.h"

sf::Vector2f ValuesTable::value_size_ = { 75.f, 20.f };

ValuesTable::ValuesTable(int vars_amount, uint64_t f_ind)
        : variables_amount_(vars_amount)
        , function_number_(f_ind)
        , vals_(CalcAllCombinations(1, vars_amount))
        , colors_(vals_.size(), std::vector<sf::Color>((1 << variables_amount_), text_color))
{
    std::sort(vals_.begin(), vals_.end());
}

void ValuesTable::SetSize(sf::Vector2f size) {
    size_ = size;
}

void ValuesTable::SetPosition(sf::Vector2f pos) {
    pos_ = pos;
}

void ValuesTable::MoveX(float dist) {
    cur_pos_.x = std::max(0.f, std::min(GetFullSize().x - size_.x, cur_pos_.x - dist));
}

void ValuesTable::MoveY(float dist) {
    cur_pos_.y = std::max(0.f, std::min(GetFullSize().y - size_.y, cur_pos_.y - dist));
}

void ValuesTable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RoundedRectangleShape back(size_);
    back.setFillColor(background_color);
    back.setRoundRadius(5);
    back.setOutlineColor(outline_color);
    back.setOutlineThickness(3);
    back.setPosition(pos_);
    target.draw(back);

    sf::RenderTexture texture;
    texture.create(static_cast<unsigned int>(size_.x) - 10, static_cast<unsigned int>(size_.y) - 10);
    texture.clear(background_color);


    sf::RectangleShape line(sf::Vector2f(net_thickness_, ((1ll << variables_amount_) + 1) * value_size_.y + net_thickness_));
    line.setFillColor(outline_color);
    for (int i = 0; i <= vals_.size() + 1; ++i) {
        line.setPosition(i * value_size_.x + 5 - cur_pos_.x, 5 - cur_pos_.y);
        texture.draw(line);
    }

    line.setSize(sf::Vector2f((1 << variables_amount_) * value_size_.x + net_thickness_, net_thickness_));
    for (int i = 0; i <= (1 << variables_amount_) + 1; ++i) {
        line.setPosition(5 - cur_pos_.x, i * value_size_.y + 5 - cur_pos_.y);
        texture.draw(line);
    }

    CenterPositionedString val;

    for (int i = 1; i <= vals_.size(); ++i) {
        for (int j = 1; j <= (1 << variables_amount_); ++j) {
            val.setBackground(colors_[i - 1][j - 1]);
            val.setString(vals_[i - 1].GetVal(j - 1, variables_amount_));
            val.setPosition(value_size_.x * i + 5 - cur_pos_.x + value_size_.x / 2, value_size_.y * j + 5 - cur_pos_.y + value_size_.y / 2);
            texture.draw(val);
        }
    }

    val.setBackground(text_color);
    for (int i = 1; i <= vals_.size(); ++i) {
        val.setString(vals_[i - 1].GetName());
        val.setPosition(5 + i * value_size_.x - cur_pos_.x + value_size_.x / 2, 5 - cur_pos_.y + value_size_.y / 2);
        texture.draw(val);
    }

    val.setPosition(value_size_.x / 2 + 5 - cur_pos_.x, value_size_.y / 2 + 5 - cur_pos_.y);
    val.setString("f");
    texture.draw(val);

    uint64_t func_copy = function_number_;
    for (int i = 0; i <= vals_.size(); ++i) {
        val.setPosition(value_size_.x / 2 - cur_pos_.x + 5, value_size_.y * (i + 1.5) - cur_pos_.y + 5);
        val.setString(func_copy & 1 ? "1" : "0");
        texture.draw(val);
        func_copy >>= 1;
    }

    texture.display();
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(pos_.x + 5, pos_.y + 5);
    target.draw(sprite);
}

std::vector<VariablesCombination> ValuesTable::CalcAllCombinations(int var, int vars_amount) {
    if (var > vars_amount) {
        return {};
    }

    std::vector<VariablesCombination> all_with_less = CalcAllCombinations(var + 1, vars_amount);
    std::vector<VariablesCombination> ans;
    ans.push_back(VariablesCombination({ VariableInFunction(var) }));
    std::copy(all_with_less.begin(), all_with_less.end(), std::back_inserter(ans));
    for (VariablesCombination i : all_with_less) {
        i.PushFront(VariableInFunction(var));
        ans.push_back(i);
    }

    return ans;
}

sf::Vector2f ValuesTable::GetFullSize() const {
    return { ((1 << variables_amount_) + 0.5f) * value_size_.x, ((1 << variables_amount_) + 2) * value_size_.y };
}

void ValuesTable::FillSameInColumn(int column, std::string val, sf::Color color) {
    for (int i = 0; i <= vals_.size(); ++i) {
        if (vals_[column].GetVal(i, variables_amount_) == val) {
            colors_[column][i] = color;
        }
    }
}

std::optional<std::string> ValuesTable::NextStepMinimizing() {
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

sf::Color ValuesTable::GetRandomColor() {
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

void ValuesTable::RemoveNextAtFunc0() {
    for (uint64_t i = 0, func_num_copy = function_number_; i <= vals_.size(); ++i, func_num_copy >>= 1) {
        if (!(func_num_copy & 1)) {
            FillSameInColumn(cur_column_, vals_[cur_column_].GetVal(i, variables_amount_), GetRandomColor());
        }
    }
    ++cur_column_;
}

std::string ValuesTable::Reduce() {
    std::map<Variant, std::set<int>> variants;

    for (int i = 1; i <= vals_.size(); ++i) {
        for (int j = 1; j <= (1 << variables_amount_); ++j) {
            if (colors_[i - 1][j - 1] == text_color) {
                variants[Variant(vals_[i - 1], vals_[i - 1].GetVal(j - 1, variables_amount_))].insert(j);
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

std::vector<std::vector<ValuesTable::Variant>> ValuesTable::CalcAllCombinationsOfVariants(std::map<ValuesTable::Variant,
                                                                                          std::set<int>>::const_iterator cur,
                                                                                          const std::map<Variant, std::set<int>> &variants) {
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

void ValuesTable::FillLineWithSubstr(int line, int from, const std::string &origin, sf::Color color) {
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

void ValuesTable::Absorption() {
    for (int i = 0; i < (1 << variables_amount_); ++i) {
        for (int j = 0; j < vals_.size(); ++j) {
            if (colors_[j][i] == text_color) {
                FillLineWithSubstr(i, j + 1, vals_[j].GetName(), sf::Color::Red);
            }
        }
    }
}

ValuesTable::Variant::Variant(VariablesCombination com, std::string con)
        : comb(std::move(com))
        , consist(std::move(con))
{}

bool ValuesTable::Variant::operator<(const ValuesTable::Variant &other) const {
    return std::pair(comb, consist) < std::pair(other.comb, other.consist);
}
