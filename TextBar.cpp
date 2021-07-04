//
// Created by evgen on 18.05.2021.
//

#include "TextBar.h"
#include <iostream>
Interface::TextBar::TextBar(int x, int y, int max_size_of_text,
                 const sf::Texture& texture, const sf::Font& font):
                 Shape(x, y, texture.getSize().x, texture.getSize().y)
{
    this->max_size_of_text = max_size_of_text;
    sprite_box.setTexture(texture);
    sprite_box.setOrigin((float)(Shape.x - Shape.mouse_x_min), (float)(Shape.y - Shape.mouse_y_min));
    sprite_box.setPosition((float)Shape.x, (float)Shape.y);

    is_active = false;

    text = "";
    visual_text.setString(text);
    visual_text.setFont(font);
    visual_text.setPosition((float)Shape.mouse_x_min, (float)Shape.mouse_y_min);
    visual_text.setCharacterSize(35);
    visual_text.setFillColor(sf::Color::Black);
    visual_text.setStyle(sf::Text::Bold);
}


void Interface::TextBar::event_holder(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (sprite_box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                this->setActive();
            else{
                this->setPassive();
            }
        }
    }

    if (this->is_active) {
        if (event.type == sf::Event::TextEntered) {
            switch (event.text.unicode) {
                case (0xD): {
                    setPassive();
                    return;
                }
                case (8):            //Backspace
                    if (text.isEmpty()) return;
                    else {
                        text.erase((text.getSize() - 1), 1);
                        visual_text.setString(text);
                        return;
                    }
                default : {
                    if (text.getSize() < max_size_of_text) {
                        text += (char) (event.text.unicode);
                        visual_text.setString(text);
                    }
                    return;
                }
            }
        }
    }
}

void Interface::TextBar::setActive(){
    is_active = true;
    sprite_box.setColor(sf::Color(128, 128, 128));
}

void Interface::TextBar::setPassive()
{
    is_active = false;
    sprite_box.setColor(sf::Color::White);
}

void Interface::TextBar::display(sf::RenderWindow& window) const
{
    window.draw(sprite_box);
    window.draw(visual_text);
}

void Interface::TextBar::setText(std::string&& str)
{
    visual_text.setString(str);
}

std::string Interface::TextBar::returnText() {
    return this->text;
}
