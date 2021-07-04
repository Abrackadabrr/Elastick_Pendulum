//
// Created by evgen on 27.06.2021.
//

#include "text.h"

Interface::text::text(float x, float y,
           std::string &&str, int character_size,
           sf::Font &font, sf::Color color,
           sf::Text::Style style){
    txt.setString(str);
    txt.setFont(font);
    txt.setCharacterSize(character_size);
    txt.setFillColor(color);
    txt.setStyle(style);
    txt.setOrigin(0, txt.getLocalBounds().height/1.15f);
    txt.setPosition(x, y);
}

void Interface::text::setString(std::string &&str)
{
    txt.setString(str);
}

void Interface::text::setPosition(float x, float y)
{
    txt.setPosition(x, y);
}

void Interface::text::display(sf::RenderWindow &window) {
    window.draw(txt);
}
