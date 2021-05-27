#include "cScreen.hpp"

class Field{
public:
    int value, pos_x, pos_y, scale;
    bool is_mine;
    bool is_flag;
    bool is_clicked;

    Field();

    bool is_pressed(int, int);
    void set_mine(int, int);
};

Field::Field() {
    is_mine = false;
    is_flag = false;
    is_clicked = false;
    value = 0;
}

bool Field::is_pressed(int x, int y) {
    if(x >= pos_x && y >= pos_y && x < pos_x+scale && y < pos_y + scale)
        return true;
    return false;
}
