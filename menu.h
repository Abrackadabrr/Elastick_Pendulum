//
// Created by evgen on 21.06.2021.
//
#ifndef MENU
#define MENU

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "properties.h"
#include "Button.h"

void lost_focus (sf::RenderWindow & window)
{
    while (true)
    {
        sf::Event event1{};
        while (window.pollEvent(event1))
        {
            switch (event1.type)
            {
                case(sf::Event::GainedFocus):
                    return;
            }
        }
    }
}

bool main_function_in_menu(bool& restart, PhaseSpace& in, Con& cnst)
{
    int DISTANCE_BETWEEN_BUTTONS = 100;
    int HEIGHT_OF_MENU = 1200;
    int WIGHT_OF_MENU = 700;
    int X_CENTER_OF_MENU =int((HEIGHT_OF_MENU)/2);
    int Y_CENTER_OF_MENU = int((WIGHT_OF_MENU)/2);

    sf::Font font;
    font.loadFromFile("../Fonts/18341.ttf");

    sf::RenderWindow window(sf::VideoMode(HEIGHT_OF_MENU, WIGHT_OF_MENU), "Main Menu",sf::Style::Titlebar);
    sf::Texture start_button_Texture, headTexture, menuTexture3, about_button_Texture, BackgroundTexture, exit_button_Texture, prop_button_Texture;
    headTexture.loadFromFile("../images/head.png");
    start_button_Texture.loadFromFile("../images/start.png");
    BackgroundTexture.loadFromFile("../images/background.jpg");
    about_button_Texture.loadFromFile("../images/about.png");
    exit_button_Texture.loadFromFile("../images/exit.png");
    prop_button_Texture.loadFromFile("../images/setprop.png");

    bool starting_animation = false;
    bool is_about_window_opend = false;
    bool is_app_closed = false;
    bool is_window_with_properties_opened = false;

    sf::Sprite head(headTexture), Bg(BackgroundTexture);

    head.setPosition(20, 0);

    Bg.setColor(sf::Color(255, 255, 255, 255)); Bg.setScale(0.7,0.7);
    Bg.setPosition(0, 0);

    Interface::Button b_start(X_CENTER_OF_MENU, Y_CENTER_OF_MENU,
                   start_button_Texture,
                   sf::Color::White, sf::Color::Green,
                   window,
                   starting_animation);
    Interface::Button b_about(X_CENTER_OF_MENU, Y_CENTER_OF_MENU + DISTANCE_BETWEEN_BUTTONS,
                   about_button_Texture,
                   sf::Color::White, sf::Color::Green,
                   window,
                   is_about_window_opend);
    Interface::Button b_exit(X_CENTER_OF_MENU, Y_CENTER_OF_MENU + 3 * DISTANCE_BETWEEN_BUTTONS,
                  exit_button_Texture,
                  sf::Color::White, sf::Color::Green,
                  window,
                  is_app_closed);
    Interface::Button b_prop(X_CENTER_OF_MENU, Y_CENTER_OF_MENU + 2 * DISTANCE_BETWEEN_BUTTONS,
                  prop_button_Texture,
                  sf::Color::White, sf::Color::Green,
                  window,
                  is_window_with_properties_opened);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            b_start.event_holder(event);
            b_about.event_holder(event);
            b_exit.event_holder(event);
            b_prop.event_holder(event);

            switch (event.type)
            {
                case(sf::Event::Closed):
                    {window.close(); return false;}
                case(sf::Event::LostFocus):
                    {lost_focus(window);}
            }
        }
        head.setColor(sf::Color::White);

        window.clear(sf::Color(129, 181, 221));

        if (starting_animation)  {window.close(); return true;};
        if (is_about_window_opend) {};
        if (is_app_closed) {window.close(); restart = false; return false;}
        if (is_window_with_properties_opened) {main_function_in_properties(in, cnst);}

        window.draw(Bg);
        window.draw(head);

        b_start.display(window);
        b_about.display(window);
        b_exit.display(window);
        b_prop.display(window);

        window.display();
    }
    return true;
}

#endif //MENU