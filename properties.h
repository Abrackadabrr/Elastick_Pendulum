//
// Created by evgen on 21.06.2021.
//

#ifndef PROPS
#define PROPS

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "TextBar.h"
#include "text.h"
#include "BasicWindow.h"
void main_function_in_properties(PhaseSpace& in, Con& cnst)
{
//____________Making_an_interface____________//
    sf::Font font;
    try{
    font.loadFromFile("../Fonts/18341.ttf");
    } catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }
    sf::Texture textboxTexture; textboxTexture.loadFromFile("../images/text_field.png");

    Interface::TextBar txt_field_length(400, 100, 12, textboxTexture, font);
    txt_field_length.setText(std::to_string(cnst.l));

    Interface::TextBar txt_field_mass(400,250,12, textboxTexture, font);
    txt_field_mass.setText(std::to_string(cnst.m));

    Interface::TextBar txt_field_g(400,400,12, textboxTexture, font);
    txt_field_g.setText(std::to_string(cnst.g));

    Interface::TextBar txt_field_k(400,550,12, textboxTexture, font);
    txt_field_k.setText(std::to_string(cnst.k));

    Interface::TextBar txt_field_phi(400,700,12, textboxTexture, font);
    txt_field_phi.setText(std::to_string(in.y));

    Interface::text t1(100, 150, "Length (meters)", 25,font);

    Interface::text t2(100, 300, "Cargo weight (kilograms) ", 25 ,font);

    Interface::text t3(100, 450, "Free fall acceleration (meters per seconds squared)", 25,font);

    Interface::text t4(100, 600, "Spring rate (Newton / meter)", 25, font);

    Interface::text t5(100, 750, "Angle start value", 25, font);

    Interface::text t6(50., 850, "When you set all properties you want, close this window", 25, font);

//________________Set window, it's event holder and display_____________________//
    sf::RenderWindow window(sf::VideoMode(800, 950), "Set properties");

    while (window.isOpen())
    {

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            txt_field_length.event_holder(event);
            txt_field_g.event_holder(event);
            txt_field_mass.event_holder(event);
            txt_field_k.event_holder(event);
            txt_field_phi.event_holder(event);
        }

        window.clear(sf::Color::White);

        txt_field_length.display(window);
        txt_field_g.display(window);
        txt_field_mass.display(window);
        txt_field_k.display(window);
        txt_field_phi.display(window);

        t1.display(window);
        t2.display(window);
        t4.display(window);
        t5.display(window);
        t6.display(window);
        t3.display(window);

        window.display();
    }
    //_______________Doing some specific things_________________//
    std::string str = txt_field_length.returnText();
    if (!str.empty()) cnst.l =std::stod(str);
    str = txt_field_g.returnText();
    if (!str.empty()) cnst.g =std::stod(str);
    str = txt_field_mass.returnText();
    if (!str.empty()) cnst.m =std::stod(str);
    str = txt_field_k.returnText();
    if (!str.empty()) cnst.k =std::stod(str);
    str = txt_field_phi.returnText();
    if (!str.empty()) in.y =std::stod(str);

//    cout << cnst->l<<endl<< cnst->g<<endl<< cnst->m<<endl<< cnst->k<<endl<< in->y<<endl;
}

#endif //PROPS