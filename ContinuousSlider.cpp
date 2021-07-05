#include "ContinuousSlider.h"


Interface::ContinuousSlider::ContinuousSlider(int x, int y, sf::RenderWindow& win): window(win)
{
	xCord = x;
	yCord = y;
	axisHeight = 5;
	axisWidth = 150;
	sliderWidth = 15;
	sliderHeight = 20;

	if (!font.loadFromFile("../Fonts/Neon.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::Black);

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(255, 50, 0));
	axis.setOutlineColor(sf::Color::Black);
	axis.setOutlineThickness(1);
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(1, 100, 32));
	slider.setOutlineThickness(1);
	slider.setOutlineColor(sf::Color::Black);
}

sf::Text Interface::ContinuousSlider::returnText(int x, int y, std::string z, int fontSize)
{
	text.setCharacterSize(fontSize);
	text.setPosition(x, y);
	text.setString(z);
	return text;
}

void Interface::ContinuousSlider::create(float min, float max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}

void Interface::ContinuousSlider::event_holder(sf::Event& event)
{
	if (slider.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
		&& event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    is_mouse_clicekd_on = !is_mouse_clicekd_on;
    if (is_mouse_clicekd_on && event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (sf::Mouse::getPosition(window).x >= xCord && sf::Mouse::getPosition(window).x <= xCord + axisWidth)
		{
			slider.setPosition(sf::Mouse::getPosition(window).x, yCord);
			sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
		}
	}
    if (event.type == sf::Event::MouseButtonReleased) is_mouse_clicekd_on = false;
}

void Interface::ContinuousSlider::setSliderValue(float newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz*diff2;
		posX += xCord;
		slider.setPosition(posX, yCord);
	}
}

void Interface::ContinuousSlider::setSliderPercentValue(float newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition(xCord + (axisWidth*newPercentValue / 100), yCord);
	}
}

void Interface::ContinuousSlider::display(sf::RenderWindow &window)
{
	window.draw(returnText(xCord - 5, yCord + 5, std::to_string(minValue).substr(0, std::to_string(minValue).length() - 4), 10));
	window.draw(axis);
	window.draw(returnText(xCord + axisWidth - 5, yCord + 5, std::to_string(maxValue).substr(0, std::to_string(maxValue).length() - 4), 10));
	window.draw(slider);
	window.draw(returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight,
                           std::to_string(sliderValue).substr(0, std::to_string(sliderValue).length() - 4), 10));
}
