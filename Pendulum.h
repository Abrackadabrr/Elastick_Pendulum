//
// Created by evgen on 01.07.2021.
//

#ifndef E_PENDULUM_H
#define E_PENDULUM_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Pendulum{

    struct PendulumElement{
        double x = 0;
        double y = 0;
        sf::Sprite sprite;
        PendulumElement(sf::Texture &image, float scale_x, float scale_y);
    };

    struct Point{
        double x;
        double y;
    };

    PendulumElement ball;
    PendulumElement starting_point;
    sf::RenderTexture path;
    bool is_path_visible = true;
    bool is_ball_visible = true;
    bool is_spring_visible = false;
    bool is_sus_point_move = true;

public:
    Pendulum(sf::Texture &ball_image, sf::Texture &starting_point_image);

    Point getSusPointPosition() const;

    void setBallPosition(const Point& pos);

    void setSusPointPosition(const Point& pos);

    void setPathVisibility(const bool& visibility);

    void setBallVisibility(const bool& visibility);

    void setSpringVisibility(const bool& visibility);

    void clearPath();

    void set_trajectory(double current_x , double current_y, double previous_x, double previous_y);

    void display(sf::RenderWindow &window);

    bool isSusPointMove() const {return is_sus_point_move;};

    void event_holder(sf::Event &event, sf::RenderWindow &window)
    {
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.mouseButton.button == sf::Mouse::Left)
                if (starting_point.sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    is_sus_point_move = !is_sus_point_move;
                    path.clear(sf::Color(0,0,0,0));
                }
        if (event.type == sf::Event::MouseMoved && is_sus_point_move){
            setSusPointPosition({sf::Mouse::getPosition(window).x / 1.f, sf::Mouse::getPosition(window).y / 1.f});
        }
    }

    bool savePathToFile(const std::string &filename);
};


#endif //E_PENDULUM_H
