#include <functional>

#include "SFML/Graphics.hpp"

#include "../prack-numbers-systems/rounded_rectangle.h"
#include "../prack-numbers-systems/general_data.h"

class InOutputField : public sf::Drawable {
 public:
    InOutputField(sf::Vector2f pos, sf::Vector2f size);

    void Click(sf::Vector2f pos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void Write(sf::Uint32 event);

    void Activate();

    void SetText(std::string s);

    std::string GetText() const {
        return data_;
    }
 private:
    sf::Vector2f pos_, size_;
    std::string data_;
    bool active_ = false;
};
