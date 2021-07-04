//
// Created by evgen on 27.06.2021.
//

#ifndef TEXTBAR_BOX_H
#define TEXTBAR_BOX_H


struct Box {
    int x; int y;
    int mouse_x_min; int mouse_x_max;
    int mouse_y_min; int mouse_y_max;

    Box(int x = 0, int y = 0, int length = 100, int width = 100): x(x), y(y){
        mouse_y_min = y - width/2;
        mouse_y_max = y + width/2;
        mouse_x_min = x - length/2;
        mouse_x_max = x + length/2;
    }

    bool contains(int x_, int y_) const{
        if (x_ <= mouse_x_max && x_ >= mouse_x_min &&
            y_ <= mouse_y_max && y_ >= mouse_y_min)
            return true;
        return false;
    }
    int get_length() const{
        return mouse_x_max - mouse_x_min;
    }
    int get_width() const {
        return mouse_y_max - mouse_y_min;
    }
};

#endif //TEXTBAR_BOX_H
