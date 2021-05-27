#include "screen_2.hpp"

class screen_4 : public cScreen
{
private:
	int alpha_max;
	bool playing;
public:
	screen_4(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_4::screen_4(void)
{
	alpha_max = 255;
	playing = false;
}

int screen_4::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	sf::Texture Texture;
	sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool is_playing_sound = false;

	Tekst Menu1("New game", 950, 210, 45, 0, 0, 0);
	Tekst Menu2("Menu", 950, 345, 45, 0, 0, 0);
	Tekst Menu3("Exit", 950, 480, 45, 0, 0, 0);

	if (!Texture.loadFromFile("images/lost.png"))
		return (-1);
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(0,0,0));
	Sprite.setScale(0.8,0.8);

	if (!Font.loadFromFile("fonts/pricedown.ttf"))
		return (-1);

	if (!buffer.loadFromFile("sounds/button-15.wav"))
		return (-1);
    sound.setBuffer(buffer);


    Menu1.load();
    Menu1.t.setFont(Font);
	Menu2.load();
	Menu2.t.setFont(Font);
	Menu3.load();
	Menu3.t.setFont(Font);

	if (playing)
	{
		alpha = alpha_max;
	}


	while (Running)
	{


        sf::Vector2i pos = sf::Mouse::getPosition(App);
        int x = pos.x;
        int y = pos.y;

        if(Menu1.change_color(x,y) || Menu2.change_color(x,y) || Menu3.change_color(x,y)) {
            if(!is_playing_sound && sound_on) {
                sound.play();
                is_playing_sound = true;
            }
        }

        else
            is_playing_sound = false;



		while (App.pollEvent(Event))
		{

			if (Event.type == sf::Event::Closed)
				return (-1);

			if (Event.type == sf::Event::MouseButtonPressed)
                if(Menu1.is_pressed(x,y)) {
                    playing = true;
                    return(3);
                }
                if(Menu2.is_pressed(x,y))
                    return(0);
                if(Menu3.is_pressed(x,y))
                    return(-1);
		}

		if (alpha<alpha_max)
			alpha++;

		App.clear(sf::Color(255,255,255));

		//rysowanie kolejno obrazka oraz wszystkich opcji menu
		App.draw(Sprite);



		if (alpha == alpha_max)
		{

            App.draw(Menu1.t);
		    App.draw(Menu2.t);
		    App.draw(Menu3.t);

		}
		App.display();

	}

	return (-1);
}
