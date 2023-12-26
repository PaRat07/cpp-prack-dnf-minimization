#include "SFML/Graphics.hpp"

#include "value_shape.h"

#include <vector>
#include <stack>

using namespace std::string_literals;

// using 1-indexation
class VariableInFunction {
 public:
    explicit VariableInFunction(int ind_of_var)
        : ind_of_var_(ind_of_var)
    {
    }

    [[nodiscard]] std::string GetName() const {
        return ""s + static_cast<char>('a' + ind_of_var_ - 1);
    }

    [[nodiscard]] bool GetValueAt(int ind) const {
        return 1 - ind / (1ll << std::abs(ind_of_var_ - 1)) % 2;
    }

    auto operator<=>(const VariableInFunction &other) const {
        return ind_of_var_ <=> other.ind_of_var_;
    }

    bool operator==(const VariableInFunction &other) const = default;
    bool operator!=(const VariableInFunction &other) const = default;
 private:
    // 1-indexation
    int ind_of_var_;
};