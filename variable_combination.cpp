#include "variable_combination.h"

VariablesCombination::VariablesCombination(std::deque<VariableInFunction> vars)
        : vars_(std::move(vars))
{
}

std::string VariablesCombination::GetName() const {
    std::string ans;
    for (const auto &i : vars_) {
        ans += i.GetName();
    }
    return ans;
}

std::string VariablesCombination::GetVal(int pos, int vars_amount) const {
    std::string ans;
    for (const auto &i : vars_) {
        ans += (i.GetValueAt(pos, vars_amount) ? '1' : '0');
    }
    return ans;
}

void VariablesCombination::PushFront(VariableInFunction var) {
    vars_.push_front(var);
}

bool VariablesCombination::operator<(const VariablesCombination &other) const {
    if (vars_.size() < other.vars_.size()) {
        return true;
    } else if (vars_.size() > other.vars_.size()) {
        return false;
    } else {
        return std::lexicographical_compare(vars_.begin(), vars_.end(), other.vars_.begin(), other.vars_.end());
    }
}
