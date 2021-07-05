//
// Created by evgen on 06.07.2021.
//

#ifndef ELASTIC_PENDULUM_FUNCTIONBASEDBUTTON_H
#define ELASTIC_PENDULUM_FUNCTIONBASEDBUTTON_H
using vv_func_ptr = void (*) ();

namespace Interface {
    namespace Button {
        class FunctionBasedButton : public ButtonFrame {
            vv_func_ptr synchronised_function;

        public:
            FunctionBasedButton(sf::RenderWindow &win,int x, int y, const sf::Texture &texture,
                                sf::Color first_color, sf::Color second_color, vv_func_ptr func):
                                ButtonFrame(win ,x, y, texture, first_color, second_color), synchronised_function(func) {};

            FunctionBasedButton(sf::RenderWindow &win, int x, int y, const sf::Font &font, std::string text, int charecter_size,
                    sf::Color first_color, sf::Color second_color, vv_func_ptr fucn):
            ButtonFrame(win, x, y, font, text, charecter_size, first_color, second_color),
            synchronised_function(fucn) {};

            void button_function() override{
                synchronised_function();
            }
        };
    }
}
#endif //ELASTIC_PENDULUM_FUNCTIONBASEDBUTTON_H
