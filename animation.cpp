//
// Created by evgen on 21.06.2021.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "calculation.h"
#include "menu.h"
#include "Pendulum.h"
#include "ChoiseBar.h"
#include "text.h"
#include "TextBar.h"
#include "ContinuousSlider.h"

using sf::Event;
using sf::RenderWindow;
using sf::Texture;
using sf::Keyboard;

void pause(RenderWindow &window, bool &restart) {
    while (true) {
        Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (Event::Closed): {
                    window.close();
                    restart = false;
                    return;
                };
                case (Event::KeyReleased): {
                    if (event.key.code == Keyboard::Space) return;
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                        return;
                    };
                }
            }
        }
    }
}

int animation(bool &restart) {
    const int DRAWS_FREQUENCY = 1;  // how often do you want to display a new step TODO
    const int WINDOW_SIZE_X = 860;
    const int WINDOW_SIZE_Y = 860;
    const int SCALE_FACTOR_OF_SCALE_FACTOR = 20;
    int scale_factor = 2000;
    double all_time = 0;  // real all time
    int amount_of_draws = 0;  // param that helps us count an iterations

    sf::Clock clock;

    // Loading some textures and changed it's parameters
    sf::Font font;
    font.loadFromFile("../Fonts/20011.ttf");
    Texture sus_point_texture;
    sus_point_texture.loadFromFile("../images/podvass.png");
    Texture ball_texture;
    ball_texture.loadFromFile("../images/ball.png");
    Texture background_texture;
    background_texture.loadFromFile("../images/background1.jpg");
    ball_texture.setSmooth(true);
    sf::Sprite background_sprite(background_texture);
    background_sprite.setScale(0.7, 0.7);

    // Creation of pendulum
    Pendulum pendulum(ball_texture, sus_point_texture);
    pendulum.setSusPointPosition({(sf::Mouse::getPosition().x / 1.), (sf::Mouse::getPosition().y / 1.)});
    // Init of some constants (not in program, but in real world)
    Con cnst{0.16, 1, 9.81, 100};
    PhaseSpace previous_step{((cnst.m * cnst.g) / cnst.k), 1. / 2, 0, 0};  // initial conditions
    PhaseSpace k[5];  // params for RK4
    k[0].x = 0;
    k[0].y = 0;
    k[0].vx = 0;
    k[0].vy = 0;

    if (!main_function_in_menu(restart, previous_step, cnst)) return 0;
    RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Elastic pendulum", sf::Style::Titlebar);
    if (cnst.m < 1) {
        cnst.m *= 10;
        cnst.k *= 10;
    }
    previous_step.x = ((cnst.m * cnst.g) / cnst.k) - ((cnst.m * cnst.g) / cnst.k) / 2.5;

    // Creation of an interface
    bool is_animation_dont_runs = false;
    Interface::Button::BoolTypeButton button_back(window, 730, 30, font, "To main menu", 20, \
    sf::Color(255, 50, 0), sf::Color(1, 100, 32), is_animation_dont_runs);

    Interface::ChoiseBar path_visibility_chose(50, 30, 10, 3, sf::Color(255, 50, 0),\
                                        sf::Color(1, 100, 32), false);
    Interface::text path_visibility_text(70, 30, "Path visibility", 20, font, sf::Color(255, 50, 0), sf::Text::Style::Bold);
    Interface::ChoiseBar ball_visibility_chose(50, 60, 10, 3, sf::Color(255, 50, 0),\
                                        sf::Color(1, 100, 32), true);
    Interface::text ball_visibility_text(70, 60, "Ball visibility", 20, font, sf::Color(255, 50, 0), sf::Text::Style::Bold);
    Interface::ChoiseBar spring_visibility_chose(50, 90, 10, 3, sf::Color(255, 50, 0),\
                                        sf::Color(1, 100, 32), true);
    Interface::text spring_visibility_text(70, 90, "Spring visibility", 20, font, sf::Color(255, 50, 0), sf::Text::Style::Bold);
    Interface::ChoiseBar::active = 2;
    Interface::ChoiseBar::amount_of_turned_on_together_bars = 3;

    Interface::ContinuousSlider speed_slider(50, 120, window);
    speed_slider.create(0.1, 2);
    speed_slider.setSliderValue(1);
    Interface::text speed_slider_text(45, 160, "Speed", 20, font, sf::Color(255, 50, 0), sf::Text::Style::Bold);

    while (window.isOpen()) {
        clock.restart();

        Event event{};
        while (window.pollEvent(event)) {
            pendulum.event_holder(event, window);
            button_back.event_holder(event);
            path_visibility_chose.event_holder(event);
            ball_visibility_chose.event_holder(event);
            speed_slider.event_holder(event);
            spring_visibility_chose.event_holder(event);
            if (event.type == Event::Closed) {
                window.close();
                restart = false;
                return 0;
            }
            if (event.type == Event::KeyReleased) { if (event.key.code == sf::Keyboard::Space) pause(window, restart); }
            if (event.type == Event::EventType::MouseWheelMoved) {
                scale_factor += SCALE_FACTOR_OF_SCALE_FACTOR * event.mouseWheel.delta;
                pendulum.clearPath();
            }
            pendulum.setPathVisibility(path_visibility_chose.return_value());
            pendulum.setBallVisibility(ball_visibility_chose.return_value());
            pendulum.setSpringVisibility(spring_visibility_chose.return_value());

            if (is_animation_dont_runs) window.close();
        }
        PhaseSpace current_step;
        if (!pendulum.isSusPointMove()) current_step = Calculation::next_step(previous_step, k, cnst);
        else current_step = previous_step;

        if (amount_of_draws % (DRAWS_FREQUENCY) == 0) {
            window.clear(sf::Color(197,178,232, 255));

            pendulum.setBallPosition({(pendulum.getSusPointPosition().x +
                                       scale_factor * (cnst.l + current_step.x) * sin(current_step.y)),
                                      (pendulum.getSusPointPosition().y +
                                       scale_factor * (cnst.l + current_step.x) * cos(current_step.y))});

            pendulum.set_trajectory(
                    (pendulum.getSusPointPosition().x + scale_factor * (cnst.l + current_step.x) * sin(current_step.y)),
                    (pendulum.getSusPointPosition().y + scale_factor * (cnst.l + current_step.x) * cos(current_step.y)),
                    (pendulum.getSusPointPosition().x +
                     scale_factor * (cnst.l + previous_step.x) * sin(previous_step.y)),
                    (pendulum.getSusPointPosition().y +
                     scale_factor * (cnst.l + previous_step.x) * cos(previous_step.y)));

//            window.draw(background_sprite);
            pendulum.display(window);
            button_back.display(window);
            path_visibility_chose.display(window);
            path_visibility_text.display(window);
            ball_visibility_chose.display(window);
            ball_visibility_text.display(window);
            spring_visibility_chose.display(window);
            spring_visibility_text.display(window);
            speed_slider.display(window);
            speed_slider_text.display(window);
            window.display();
        }
        previous_step = current_step;
        double time = clock.getElapsedTime().asMilliseconds();
        double time_limit = TIMESTEP * 1000 * (1 / speed_slider.getSliderValue());
        std::cout << speed_slider.getSliderValue() << std::endl;
        while (time < time_limit) {
            time = clock.getElapsedTime().asMilliseconds();
        }
        all_time = all_time + time;
        amount_of_draws++;
    }

    std::cout << "real time:\t\t\t\t\t\t" << all_time << std::endl << "count time:\t\t\t\t\t\t" \
              << TIMESTEP * amount_of_draws << std::endl \
              << "amount if iterations: \t\t\t" << amount_of_draws << std::endl << std::endl;
    return 0;
}

int main() {
    bool restart = true;
    while (restart)
        animation(restart);
    return 0;
}
