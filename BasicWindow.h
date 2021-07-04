//
// Created by evgen on 02.07.2021.
//

#ifndef E_BASICWINDOW_H
#define E_BASICWINDOW_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ChoiseBar.h"
#include "text.h"
#include <vector>
#include <algorithm>
class BasicWindow{
    sf::RenderWindow window;
    std::vector<Interface::Button> buttons {};
    std::vector<Interface::ChoiseBar> chose_bars {};
    std::vector<Interface::text> texts {};
    std::vector<Interface::TextBar> text_bars {};

    BasicWindow() = default;

    void display() {
        std::for_each(buttons.begin(), buttons.end(), [this](Interface::Button &b) {b.display(window);});
        std::for_each(chose_bars.begin(), chose_bars.end(), [this](Interface::ChoiseBar &b) {b.display(window);});
        std::for_each(text_bars.begin(), text_bars.end(), [this](Interface::TextBar &b) {b.display(window);});
        std::for_each(texts.begin(), texts.end(), [this](Interface::text &b) {b.display(window);});
    }

    void interface_event_holder(const sf::Event &event){
        std::for_each(buttons.begin(), buttons.end(), [event](Interface::Button &b) {b.event_holder(event);});
        std::for_each(chose_bars.begin(), chose_bars.end(), [event](Interface::ChoiseBar &b) {b.event_holder(event);});
        std::for_each(text_bars.begin(), text_bars.end(), [event](Interface::TextBar &b) {b.event_holder(event);});
    }

    virtual void window_event_holder() = 0;

    virtual void other_window_things() {};
};
#endif //E_BASICWINDOW_H
