//
// Created by evgen on 18.05.2021.
//

#ifndef TEXTBAR_BUTTON_H
#define TEXTBAR_BUTTON_H

#include <SFML/Graphics.hpp>
#include "Box.h"

namespace Interface {
    namespace Button {
        class ButtonFrame {
        protected:
            sf::RenderWindow &window;
            Box Shape;
            sf::Text text_in_button;
            sf::Sprite sprite;
            sf::Color first_color;
            sf::Color second_color;

            void cursor_in();

            void cursor_out();

        public:
            /*
             * Constructor with a texture
             */
            ButtonFrame(sf::RenderWindow &win, int x, int y, const sf::Texture &texture,
                        sf::Color first_color, sf::Color second_color);

            /*
             * Constructor with a text
             */
            ButtonFrame(sf::RenderWindow &win, int x, int y, const sf::Font &font, std::string text, int charecter_size,
                        sf::Color first_color, sf::Color second_color);

            /*
             * Display button on Window
             */
            virtual void display(sf::RenderWindow &Window);

            /*
             * Function that processes sf::Event(s)
             */
            void event_holder(sf::Event &event);

            /*
             * Vital function for button's life
             */
            virtual void button_function() = 0;
        };
    }
}
#endif //TEXTBAR_BUTTON_H
