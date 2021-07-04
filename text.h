//
// Created by evgen on 27.06.2021.
//

#ifndef E_TEXT_H
#define E_TEXT_H
#include <SFML/Graphics.hpp>
namespace Interface {
    class text {
    private:
        sf::Text txt;
    public:
        text(float x, float y,
             std::string &&str, int character_size,
             sf::Font &font, sf::Color color = sf::Color::Black, sf::Text::Style style = sf::Text::Style::Italic);

        void setString(std::string &&str);

        void setPosition(float x, float y);

        void display(sf::RenderWindow &window);
    };
}
#endif //E_TEXT_H
