#include "button.hpp"

extern bool sound_on = true;
extern bool music_on = true;
extern int mines = 10;
extern int quanity = 10;

class screen_2 : public cScreen
{
private:
	int alpha_max;
public:
	screen_2(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_2::screen_2(void)
{
	alpha_max = 255;
}

int screen_2::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	bool is_easy = true;
	sf::Texture Texture;
	sf::Sprite Sprite;
	sf::Texture Texture1;
	sf::Sprite Sprite1;
	sf::Image Image1;
	sf::Texture Texture2;
	sf::Sprite Sprite2;
	sf::Image Image2;
    sf::Texture Texture3;
	sf::Sprite Sprite3;
	sf::Image Image3;
    sf::Texture Texture4;
	sf::Sprite Sprite4;
	sf::Image Image4;
	int alpha = 0;
	sf::Font Font;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool is_playing_sound = false;
	Tekst Menu1("Sounds", 196, 210);
	Tekst Menu2("Music", 200, 340);
	Tekst Menu7("Poziom: latwy", 200, 470);
	Tekst Menu8("Poziom: trudny", 200, 470);
    Tekst Menu4("back", 100, 650, 20);
	Tekst Menu5("exit", 100, 700, 20);
	Tekst Menu6("Settings", 275, 25, 55);
	sf::Music music;

	if (!Texture.loadFromFile("images/tree.png"))
		return (-1);
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));

    if(!Image1.loadFromFile("images/sound_on.png"))
        return (-1);
    Image1.createMaskFromColor(sf::Color::Black);
    Texture1.loadFromImage(Image1);
	Sprite1.setTexture(Texture1);
	Sprite1.scale(0.3, 0.3);
	Sprite1.setPosition(320,214);
	Sprite1.setColor(sf::Color(255, 255, 255, 255));

    if(!Image2.loadFromFile("images/sound_off.png"))
        return(-1);
    Image2.createMaskFromColor(sf::Color::Black);
    Texture2.loadFromImage(Image2);
	Sprite2.setTexture(Texture2);
	Sprite2.scale(0.3, 0.3);
	Sprite2.setPosition(320,214);
	Sprite2.setColor(sf::Color(255, 255, 255, 255));

    if(!Image3.loadFromFile("images/sound_on.png"))
        return(-1);
    Image3.createMaskFromColor(sf::Color::Black);
    Texture3.loadFromImage(Image3);
	Sprite3.setTexture(Texture3);
	Sprite3.scale(0.3, 0.3);
	Sprite3.setPosition(320,344);
	Sprite3.setColor(sf::Color(255, 255, 255, 255));

    if(!Image4.loadFromFile("images/sound_off.png"))
        return(-1);
    Image4.createMaskFromColor(sf::Color::Black);
    Texture4.loadFromImage(Image4);
	Sprite4.setTexture(Texture4);
	Sprite4.scale(0.3, 0.3);
	Sprite4.setPosition(320,344);
	Sprite4.setColor(sf::Color(255, 255, 255, 255));

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
    Menu2.load();
    Menu2.t.setFont(Font);
    Menu4.load();
    Menu4.t.setFont(Font);
    Menu5.load();
    Menu5.t.setFont(Font);
    Menu6.load();
    Menu6.t.setFont(Font);
    Menu7.load();
    Menu7.t.setFont(Font);
    Menu8.load();
    Menu8.t.setFont(Font);

    Menu6.t.setColor(sf::Color(255, 0, 0, 255));

	while (Running)
	{

        sf::Vector2i pos = sf::Mouse::getPosition(App);
        int x = pos.x;
        int y = pos.y;

        if(Menu1.change_color(x,y) || Menu2.change_color(x,y) || Menu4.change_color(x,y) || Menu5.change_color(x,y) ||
           Menu7.change_color(x,y) || Menu8.change_color(x,y)) {
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
                if(Menu1.is_pressed(x,y)) {
                    if(sound_on)
                        sound_on = false;
                    else
                        sound_on = true;
                }

                if(Menu2.is_pressed(x,y)) {
                    if(music_on) {
                        music_on = false;
                        music.stop();
                    }

                    else {
                        music_on = true;
                        music.play();
                    }

                }

                if(Menu4.is_pressed(x,y))
                    return(0);
                if(Menu5.is_pressed(x,y))
                    return(-1);


                if(Menu7.is_pressed(x,y)) {
                    if(is_easy) {
                        quanity = 20;
                        is_easy = false;
                    }

                    else {
                        quanity = 10;
                        is_easy = true;
                    }
                }


			}
		}

		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha));


		App.clear();


        App.draw(Sprite);

        if(sound_on)
            App.draw(Sprite1);
        else
            App.draw(Sprite2);

        if(music_on)
            App.draw(Sprite3);
        else
            App.draw(Sprite4);

        if(quanity == 10)
            App.draw(Menu7.t);
        else
            App.draw(Menu8.t);

		if (alpha == alpha_max)
		{

            App.draw(Menu1.t);
            App.draw(Menu2.t);
            App.draw(Menu4.t);
			App.draw(Menu5.t);
			App.draw(Menu6.t);
		}
		App.display();

	}

	return (-1);
}
