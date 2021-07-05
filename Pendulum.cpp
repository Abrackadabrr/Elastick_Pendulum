//
// Created by evgen on 01.07.2021.
//

#include "Pendulum.h"

Pendulum::PendulumElement::PendulumElement(sf::Texture &image, float scale_x, float scale_y)
{
    sprite.setTexture(image);
    sprite.setOrigin ((image.getSize().x) / 2.f, (image.getSize().y / 2.f));
    sprite.setScale(scale_x, scale_y);
}

Pendulum::Pendulum(sf::Texture &ball_image, sf::Texture &starting_point_image):
ball(ball_image, 0.09, 0.09),
starting_point(starting_point_image, 0.5,0.5),
path()
{
    path.create(960, 960);
    path.clear(sf::Color(0, 0, 0, 0));
}

Pendulum::Point Pendulum::getSusPointPosition() const
{
    return {starting_point.x, starting_point.y};
}

void Pendulum::setBallPosition(const Pendulum::Point &pos)
{
    ball.x = pos.x;
    ball.y = pos.y;
    ball.sprite.setPosition(pos.x / 1.f , pos.y / 1.f);
}

void Pendulum::setSusPointPosition(const Pendulum::Point &pos)
{
    starting_point.y = pos.y;
    starting_point.x = pos.x;
    starting_point.sprite.setPosition(pos.x / 1.f , pos.y / 1.f);
}

void Pendulum::setPathVisibility(const bool &visibility)
{
    is_path_visible = visibility;
}

void Pendulum::clearPath()
{
    if(is_path_visible) path.clear(sf::Color(0, 0, 0, 0));
}

void Pendulum::set_trajectory(double current_x, double current_y, double previous_x, double previous_y)
{
    if(is_path_visible)
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(current_x, current_y);
        line[1].position = sf::Vector2f(previous_x, previous_y);
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;
        path.draw(line);
        path.display();
    }
    else
    {
        path.clear(sf::Color(0,0,0,0));
        path.display();
    }
}

void Pendulum::display(sf::RenderWindow &window)
{
    sf::Sprite s(path.getTexture());
    window.draw(s);
    if (is_spring_visible) {
        sf::VertexArray spring(sf::Lines, 2);
        spring[0].position = sf::Vector2f(starting_point.x, starting_point.y);
        spring[1].position = sf::Vector2f(ball.x, ball.y);
        spring[0].color = sf::Color::Black;
        spring[1].color = sf::Color::Black;
        window.draw(spring);
    }
    if (is_ball_visible) window.draw(ball.sprite);
    window.draw(starting_point.sprite);
}

void Pendulum::setBallVisibility(const bool &visibility) {
    is_ball_visible = visibility;
}

void Pendulum::setSpringVisibility(const bool &visibility) {
    is_spring_visible = visibility;
}

bool Pendulum::savePathToFile(const std::string &filename)
{
    return path.getTexture().copyToImage().saveToFile("1.png");
}
