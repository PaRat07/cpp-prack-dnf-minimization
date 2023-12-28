#include "variable_in_function.h"

VariableInFunction::VariableInFunction(int ind_of_var)
        : ind_of_var_(ind_of_var)
{
}

std::string VariableInFunction::GetName() const {
    return ""s + static_cast<char>('a' + ind_of_var_ - 1);
}

bool VariableInFunction::GetValueAt(int ind, int vars_amount) const {
    return 1 - ind / (1ll << std::abs(vars_amount - ind_of_var_)) % 2;
}

std::strong_ordering VariableInFunction::operator<=>(const VariableInFunction &other) const {
    return ind_of_var_ <=> other.ind_of_var_;
}
