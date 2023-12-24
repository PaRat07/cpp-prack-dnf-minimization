#include "SFML/Graphics.hpp"

#include "variable_in_function.h"

#include <algorithm>
#include <vector>
#include <algorithm>

class VariablesCombination {
 public:
    VariablesCombination(std::deque<VariableInFunction> vars)
        : vars_(std::move(vars))
    {
    }

    [[nodiscard]] std::string GetName() const {
        std::string ans;
        for (const auto &i : vars_) {
            ans += i.GetName();
        }
        return ans;
    }

    [[nodiscard]] std::string GetVal(int pos) const {
        std::string ans;
        for (const auto &i : vars_) {
            ans += (i.GetValueAt(pos) ? '1' : '0');
        }
        return ans;
    }

    void PushFront(VariableInFunction var) {
        vars_.push_front(var);
    }

    auto operator<=>(const VariablesCombination &other) const {
        return std::lexicographical_compare_three_way(vars_.begin(), vars_.end(), other.vars_.begin(), other.vars_.end());
    }

 private:
    std::deque<VariableInFunction> vars_;
};