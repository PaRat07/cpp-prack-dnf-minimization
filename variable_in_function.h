#include "SFML/Graphics.hpp"

#include <vector>
#include <stack>

using namespace std::string_literals;

// using 1-indexation
class VariableInFunction {
 public:
    explicit VariableInFunction(int ind_of_var);

    [[nodiscard]] std::string GetName() const;

    [[nodiscard]] bool GetValueAt(int ind, int vars_amount) const;

    std::strong_ordering operator<=>(const VariableInFunction &other) const;

    bool operator==(const VariableInFunction &other) const = default;
    bool operator!=(const VariableInFunction &other) const = default;
 private:
    // 1-indexation
    int ind_of_var_;
};