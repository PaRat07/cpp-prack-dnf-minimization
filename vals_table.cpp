#include "vals_table.h"
sf::Vector2f ValuesTable::value_size_ = { 75.f, 20.f };

ValuesTable::ValuesTable(uint64_t vars_amount, uint64_t f_ind)
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
    texture.create(size_.x - 10, size_.y - 10);
    texture.clear(background_color);


    sf::RectangleShape line(sf::Vector2f(net_thickness_, ((1 << variables_amount_) + 1) * value_size_.y + net_thickness_));
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
            val.setString(vals_[i - 1].GetVal(j - 1));
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
        if (vals_[column].GetVal(i) == val) {
            colors_[column][i] = color;
        }
    }
}
