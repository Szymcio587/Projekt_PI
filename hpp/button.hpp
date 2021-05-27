#include "mines.hpp"

// klasa tworząca tekst
class Tekst{
public:
    int red, green, blue, siz, secs;
    std::string text;
    float position_x, position_y;
    sf::Text t;

    Tekst(std::string = "text", float = 600, float = 20, int = 30, int = 255, int = 255, int = 255); //konstruktor

    void load();
    bool change_color(int, int);
    bool is_pressed(int, int);
};

Tekst::Tekst(std::string t, float pos_x, float pos_y, int s, int r, int g, int b) {
    text = t;
    position_x = pos_x;
    position_y = pos_y;
    siz = s;
    red = r;
    green = g;
    blue = b;
}

void Tekst::load() {
    t.setCharacterSize(siz);
    t.setString(text);

    sf::FloatRect Rect = t.getLocalBounds();
    t.setOrigin(Rect.left + Rect.width/2, Rect.top);
    t.setPosition(t.getLocalBounds().left+position_x,t.getLocalBounds().top+position_y);
}

bool Tekst::is_pressed(int x, int y) {
    if(this->t.getGlobalBounds().contains(x, y))
        return true;

    return false;
}

bool Tekst::change_color(int x, int y) {
    if(this->t.getGlobalBounds().contains(x, y)) {
        this->t.setColor(sf::Color(255,0,0));
        return true;
    }

    else
        this->t.setColor(sf::Color(red,green,blue));

    return false;

}
