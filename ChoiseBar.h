//
// Created by evgen on 18.05.2021.
//

#ifndef ONEBAR_H
#define ONEBAR_H
#include <SFML/Graphics.hpp>
namespace Interface {
    class ChoiseBar {
    public:
        static int active;
        static int amount_of_turned_on_together_bars;
    private:
        sf::Color back_color;
        sf::Color main_color;
        float x;
        float y;
        bool value;
        sf::RenderWindow win;
        sf::CircleShape ext_circle;
        sf::CircleShape int_circle;

        bool is_in(int x, int y) {
            return ext_circle.getGlobalBounds().contains(x, y);
        }

    public:
        ChoiseBar(int x, int y, int radius, int dr, sf::Color back_color, sf::Color main_color,
                  const bool &start_value) {
            value = start_value;
            this->back_color = back_color;
            this->main_color = main_color;

            this->x = x;
            this->y = y;

            ext_circle.setRadius((float) radius - 0);
            ext_circle.setFillColor(back_color);
            ext_circle.setOutlineThickness(1);
            ext_circle.setOutlineColor(sf::Color::Black);
            ext_circle.setOrigin(radius / 1.f, radius / 1.f);
            ext_circle.setPosition(x, y);

            int_circle.setRadius((float) radius - dr / 1.f);
            int_circle.setFillColor(main_color);
            int_circle.setOrigin(radius / 1.f - dr, radius / 1.f - dr);
            int_circle.setPosition(x / 1.f, y / 1.f);
        }

        void display(sf::RenderWindow &window) {
            if (active >= amount_of_turned_on_together_bars && !this->value)
                this->ext_circle.setFillColor(sf::Color(128, 128, 128));
            else
                this->ext_circle.setFillColor(this->back_color);

            window.draw(this->ext_circle);
            if (this->value)
                window.draw(this->int_circle);
        }

        void event_holder(const sf::Event &event) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (this->is_in(event.mouseButton.x, event.mouseButton.y))
                        if (active < amount_of_turned_on_together_bars || value) {
                            value = !value;
                            if (value) active++; else active--;
                        }
                }
            }
        }

        bool return_value() const {
            return this->value;
        }
    };
    int ChoiseBar::active = 0;
    int ChoiseBar::amount_of_turned_on_together_bars = 1;
}
#endif //ONEBAR_H
