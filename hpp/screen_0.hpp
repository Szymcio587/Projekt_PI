#include "screen_1.hpp"
//utworzenie klasy, która pozwala załadować dany ekran, w tym przypadu menu głowne
class screen_0 : public cScreen
{
private:
	int alpha_max;
public:
	screen_0(void); // konstruktor
	virtual int Run(sf::RenderWindow &App); //funkcja wywołująca całą zawartość na ekran
};

screen_0::screen_0(void)
{
	alpha_max = 255;
}

int screen_0::Run(sf::RenderWindow &App)
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

	//zmienne przechowujące tekst, utworzone zgodnie z plikiem button.hpp
	Tekst Menu1("start", 200, 210);
	Tekst Menu2("settings", 200, 345);
	Tekst Menu3("credits", 200, 480);
	Tekst Menu4("exit", 200, 615);
	Tekst Menu6("Welcome to minesweeper!", 275, 25, 55);

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


	//załadowanie tekstu oraz przypisanie mu czcionki
    Menu1.load();
    Menu1.t.setFont(Font);
	Menu2.load();
	Menu2.t.setFont(Font);
	Menu3.load();
	Menu3.t.setFont(Font);
	Menu4.load();
	Menu4.t.setFont(Font);
    Menu6.load();
    Menu6.t.setFont(Font);

    Menu6.t.setColor(sf::Color(255, 0, 0, 255));



	//głowna pętla gry
	while (Running)
	{


        //zapisywanie współrzędnych położenia kursora
        sf::Vector2i pos = sf::Mouse::getPosition(App);
        int x = pos.x;
        int y = pos.y;

        //zmiana koloru tekst w przypadku najechania na niego myszką
        if(Menu1.change_color(x,y) || Menu2.change_color(x,y) || Menu3.change_color(x,y) || Menu4.change_color(x,y)) {
            if(!is_playing_sound && sound_on) {
                sound.play();
                is_playing_sound = true;
            }
        }

        else
            is_playing_sound = false;


        //reagowanie na ewentualne działania użytkownika/gracza
		while (App.pollEvent(Event))
		{

			if (Event.type == sf::Event::Closed) //kliknięcie X w prawym górnym rogu
			{
				return (-1);
			}

			if (Event.type == sf::Event::MouseButtonPressed) //kliknięcie myszką na daną opcję
			{
                if(Menu1.is_pressed(x,y)) { // metody sprawdzające ten warunek
                    return(3);
                }

                if(Menu2.is_pressed(x,y))
                    return(2);
                if(Menu3.is_pressed(x,y))
                    return(1);
                if(Menu4.is_pressed(x,y))
                    return(-1);
			}
		}

		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha));

		App.clear();

		//rysowanie kolejno obrazka oraz wszystkich opcji menu
		App.draw(Sprite);



		if (alpha == alpha_max)
		{
            App.draw(Menu1.t);
		    App.draw(Menu2.t);
		    App.draw(Menu3.t);
			App.draw(Menu4.t);
			App.draw(Menu6.t);
		}
		App.display();

	}

	return (-1);
}
