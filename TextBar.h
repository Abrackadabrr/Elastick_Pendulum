//
// Created by evgen on 18.05.2021.
//

#ifndef TEXTBAR_TEXTBAR_H
#define TEXTBAR_TEXTBAR_H
#include <SFML/Graphics.hpp>
#include "Box.h"
namespace Interface {
    class TextBar {
    private:
        Box Shape;
        sf::String text;
        sf::Text visual_text;
        sf::Sprite sprite_box;
        bool is_active;
        int max_size_of_text;

    public:

        TextBar(int x, int y, int max_size_of_text,
                const sf::Texture &texture, const sf::Font &font);


        void setActive();

        void setPassive();

        void display(sf::RenderWindow &window) const;

        void setText(std::string &&str);

        void event_holder(const sf::Event &event);

        std::string returnText();
    };
}

#endif //TEXTBAR_TEXTBAR_H
