//
// Created by evgen on 05.07.2021.
//

#ifndef ELASTIC_PENDULUM_BOOLTYPEBUTTON_H
#define ELASTIC_PENDULUM_BOOLTYPEBUTTON_H
#include "ButtonFrame.h"

namespace Interface {
    namespace Button {
        class BoolTypeButton: public ButtonFrame {
            bool &synchronised_value;
        public:
            BoolTypeButton(sf::RenderWindow &win,int x, int y, const sf::Texture &texture,
                           sf::Color first_color, sf::Color second_color, bool& value):
                           ButtonFrame(win ,x, y, texture, first_color, second_color), synchronised_value(value){};

            BoolTypeButton(sf::RenderWindow &win, int x, int y, const sf::Font &font, std::string text, int charecter_size,
                           sf::Color first_color, sf::Color second_color, bool& value):
                           ButtonFrame(win, x, y, font, text, charecter_size, first_color, second_color),
                           synchronised_value(value) {};

            void button_function() override {synchronised_value = true;};

            void display(sf::RenderWindow &Window) override {
                Window.draw(sprite);
                Window.draw(text_in_button);
                synchronised_value = false;
            }
        };
    }
}

#endif //ELASTIC_PENDULUM_BOOLTYPEBUTTON_H
