//
// Created by evgen on 18.05.2021.
//

#include "Button.h"
#include <iostream>
#include "Box.h"

Interface::Button::Button(int x, int y, const sf::Texture &texture,
               sf::Color first_color, sf::Color second_color, const sf::RenderWindow &window,
               const bool &synchronized_value) :
        Shape(x, y, texture.getSize().x, texture.getSize().y), synchronized_value(const_cast<bool &>(synchronized_value)),
        window(const_cast<sf::RenderWindow &>(window)) {

    this->sprite.setTexture(texture);
    this->sprite.setOrigin((float) (this->Shape.x - this->Shape.mouse_x_min),
                           (float) (this->Shape.y - this->Shape.mouse_y_min));

    this->sprite.setPosition((float) this->Shape.x, (float) this->Shape.y);

    this->first_color = first_color;
    this->second_color = second_color;
}

Interface::Button::Button(int x, int y, const sf::Font &font, const std::string& text, int charecter_size,
               sf::Color first_color, sf::Color second_color, const sf::RenderWindow &window, const bool &synchronized_value) :
        synchronized_value(const_cast<bool &>(synchronized_value)), window(const_cast<sf::RenderWindow &>(window)),
        text_in_button(text, font, charecter_size)
{
    this->first_color = first_color;
    this->second_color = second_color;

    this->first_color = first_color;
    this->second_color = second_color;

    auto l = this->text_in_button.getGlobalBounds().height;
    auto f = this->text_in_button.getGlobalBounds().width;

    Shape = Box(x, y, f, l);

    this->text_in_button.setOrigin(f / 1.85, l /1.15); // it's math podgon

    this->text_in_button.setPosition((float) Shape.x, (float) Shape.y);
    this->text_in_button.setFillColor(first_color);
    this->text_in_button.setStyle(sf::Text::Bold);
    text_in_button.setCharacterSize(charecter_size);
}

void Interface::Button::event_holder(const sf::Event &event) {

    auto position = sf::Mouse::getPosition(this->window);
    if (Shape.contains(position.x, position.y)) { this->cursor_in(); }
    else { this->cursor_out(); }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (Shape.contains(event.mouseButton.x, event.mouseButton.y)) {
                cursor_in();
                change_synchronized_value();
            } else {
                cursor_out();
            }
        }
    }
}

void Interface::Button::cursor_in() {
    if (!text_in_button.getString().isEmpty())
        text_in_button.setFillColor(second_color);
    sprite.setColor(second_color);
}

void Interface::Button::cursor_out() {
    sprite.setColor(first_color);
    text_in_button.setFillColor(first_color);
}

void Interface::Button::display(sf::RenderWindow &Window){
    Window.draw(sprite);
    if (!text_in_button.getString().isEmpty())
        Window.draw(text_in_button);
    synchronized_value = false;
}

void Interface::Button::change_synchronized_value() {
    synchronized_value = !synchronized_value;
}
