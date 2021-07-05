#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Interface {
    class ContinuousSlider {
        sf::RenderWindow &window;
        sf::RectangleShape slider;
        sf::RectangleShape axis;
        sf::Font font;
        sf::Text text;
        float minValue;
        float maxValue;
        int xCord;
        int yCord;
        int axisWidth;
        int axisHeight;
        int sliderWidth;
        int sliderHeight;
        float sliderValue;
        bool is_mouse_clicekd_on = false;

        sf::Text returnText(int x, int y, std::string z, int fontSize);

    public:
        ContinuousSlider(int x, int y, sf::RenderWindow &win);

        void create(float min, float max);

        void event_holder(sf::Event &event);

        float getSliderValue() const {return sliderValue;};

        void setSliderValue(float newValue);

        void setSliderPercentValue(float newPercentValue);

        void display(sf::RenderWindow &window);
    };
}
