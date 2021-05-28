#include "screen_4.hpp"

class screen_1 : public cScreen
{
private:
	int alpha_max;
public:
	screen_1(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_1::screen_1(void)
{
	alpha_max = 255;
}

int screen_1::Run(sf::RenderWindow &App)
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
    sf::Music music;

	Tekst Menu1("Szymon Talar", 450, 270, 45);
	Tekst Menu4("back", 100, 650, 20);
	Tekst Menu5("exit", 100, 700, 20);
	Tekst Menu6("The game was made by:", 290, 25, 55);

	if (!Texture.loadFromFile("images/tree.png"))
		return (-1);
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));

	if (!Font.loadFromFile("fonts/pricedown.ttf"))
		return (-1);

    if (!buffer.loadFromFile("sounds/button-15.wav"))
		return (-1);
    sound.setBuffer(buffer);

    if (!music.openFromFile("sounds/NEVERGONNAGIVEYOUUP.wav"))
		return (-1);
    if(music_on)
        music.play();



    Menu1.load();
    Menu1.t.setFont(Font);
	Menu4.load();
	Menu4.t.setFont(Font);
    Menu5.load();
    Menu5.t.setFont(Font);
    Menu6.load();
    Menu6.t.setFont(Font);

    Menu6.t.setColor(sf::Color(255, 0, 0, 255));


	while (Running)
	{

        sf::Vector2i pos = sf::Mouse::getPosition(App);
        int x = pos.x;
        int y = pos.y;

        if( Menu4.change_color(x,y) || Menu5.change_color(x,y)) {
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
			{
				return (-1);
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
                if(Menu4.is_pressed(x,y))
                    return(0);
                if(Menu5.is_pressed(x,y))
                    return(-1);
			}
		}

		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha));


		App.clear();

		App.draw(Sprite);

		if (alpha == alpha_max)
		{
            App.draw(Menu1.t);
            App.draw(Menu5.t);
			App.draw(Menu4.t);
			App.draw(Menu6.t);
		}
		App.display();

	}

	return (-1);
}
