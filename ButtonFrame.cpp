//
// Created by evgen on 18.05.2021.
//

#include "ButtonFrame.h"
#include <iostream>
#include "Box.h"

Interface::Button::ButtonFrame::ButtonFrame(sf::RenderWindow &window, int x, int y, const sf::Texture &texture,
                                            sf::Color first_color, sf::Color second_color):
        Shape(x, y, texture.getSize().x, texture.getSize().y), window(window){

    this->sprite.setTexture(texture);
    this->sprite.setOrigin((float) (this->Shape.x - this->Shape.mouse_x_min),
                           (float) (this->Shape.y - this->Shape.mouse_y_min));

    this->sprite.setPosition((float) this->Shape.x, (float) this->Shape.y);

    this->first_color = first_color;
    this->second_color = second_color;
    auto l = this->text_in_button.getGlobalBounds().height;
    auto f = this->text_in_button.getGlobalBounds().width;
    this->text_in_button.setOrigin(f / 1.85, l / 1.15);

    this->text_in_button.setPosition((float) Shape.x, (float) Shape.y);
    this->text_in_button.setFillColor(first_color);
    this->text_in_button.setStyle(sf::Text::Bold);
}

Interface::Button::ButtonFrame::ButtonFrame(sf::RenderWindow &window, int x, int y, const sf::Font &font, std::string text,
                                            int charecter_size,sf::Color first_color, sf::Color second_color):
                          window(window),
                          text_in_button(text, font, charecter_size){
    this->first_color = first_color;
    this->second_color = second_color;

    this->first_color = first_color;
    this->second_color = second_color;

    auto l = this->text_in_button.getGlobalBounds().height;
    auto f = this->text_in_button.getGlobalBounds().width;

    Shape = Box(x, y, f, l);

    this->text_in_button.setOrigin(f / 1.85, l / 1.15);

    this->text_in_button.setPosition((float) Shape.x, (float) Shape.y);
    this->text_in_button.setFillColor(first_color);
    this->text_in_button.setStyle(sf::Text::Bold);
}

void Interface::Button::ButtonFrame::event_holder(sf::Event &event) {
    auto position = sf::Mouse::getPosition(window);
    if (Shape.contains(position.x, position.y)) { cursor_in(); }
    else { cursor_out(); }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (Shape.contains(event.mouseButton.x, event.mouseButton.y)) {
                cursor_in();
                button_function();
            }
            else {
                cursor_out();
            }
        }
    }
}

void Interface::Button::ButtonFrame::cursor_in() {
    this->text_in_button.setFillColor(this->second_color);
    this->sprite.setColor(second_color);
}

void Interface::Button::ButtonFrame::cursor_out() {
    this->sprite.setColor(sf::Color::White);
    this->text_in_button.setFillColor(this->first_color);
}

void Interface::Button::ButtonFrame::display(sf::RenderWindow &Window){
    Window.draw(this->sprite);
    Window.draw(this->text_in_button);
}
