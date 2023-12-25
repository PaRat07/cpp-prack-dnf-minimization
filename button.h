#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <functional>

#include "rounded_rectangle.h"
#include "general_data.h"

class Button : public sf::Drawable {
 public:
    Button(sf::Vector2f pos, sf::Vector2f sz, std::string path, const std::function<void()> &cb);

    void Click(sf::Vector2f pos) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    const std::function<void()> &callback_;
    std::string path_to_png_;
    sf::Vector2f size_, pos_;
};
