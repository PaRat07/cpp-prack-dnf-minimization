#include "SFML/Graphics.hpp"

#include "variable_in_function.h"

#include <algorithm>
#include <vector>
#include <algorithm>

class VariablesCombination {
 public:
    explicit VariablesCombination(std::deque<VariableInFunction> vars);

    [[nodiscard]] std::string GetName() const;

    [[nodiscard]] std::string GetVal(int pos, int vars_amount) const;

    void PushFront(VariableInFunction var);

    bool operator<(const VariablesCombination &other) const;

    [[nodiscard]] const std::deque<VariableInFunction> &GetVars() const {
        return vars_;
    }

 private:
    std::deque<VariableInFunction> vars_;
};