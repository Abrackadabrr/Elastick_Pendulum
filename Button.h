//
// Created by evgen on 18.05.2021.
//

#ifndef TEXTBAR_BUTTON_H
#define TEXTBAR_BUTTON_H
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "text.h"
namespace Interface {
    class Button {
    private:
        sf::RenderWindow &window;
        Box Shape;
        sf::Text text_in_button;
        sf::Sprite sprite;
        bool &synchronized_value;
        sf::Color first_color;
        sf::Color second_color;

        void change_synchronized_value();

        void cursor_in();

        void cursor_out();

    public:

        Button(int x, int y, const sf::Texture &texture,
               sf::Color first_color, sf::Color second_color,
               const sf::RenderWindow &window, const bool &synchronized_value);

        Button(int x, int y, const sf::Font &font, const std::string& text, int charecter_size,
               sf::Color first_color, sf::Color second_color, const sf::RenderWindow &window,
               const bool &synchronized_value);

        void display(sf::RenderWindow &Window);

        void event_holder(const sf::Event &event);
    };
}
#endif //TEXTBAR_BUTTON_H
