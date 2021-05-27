#include "screen_2.hpp"

extern bool win = false;

class screen_3 : public cScreen {
public:
	virtual int Run(sf::RenderWindow &App);
};

int screen_3::Run(sf::RenderWindow &App)
{
    sf::Clock Clock;
    sf::Event Event;
    bool Running = true, is_playing_sound = false;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    sf::Music music;
    sf::Texture Texture[12];
    sf::Sprite Sprite[mines][mines];
    sf::Font Font;
    Field fields[mines][mines];
    int rand_x, rand_y, mins=0, secs=0, hours=0;
    Tekst Tekst1("Czas Gry:", 900, 200, 40);
    Tekst Tekst3("Liczba min: " + std::to_string(quanity), 900, 340, 40);
    Tekst Tekst2(std::to_string(hours) + ":" + std::to_string(mins) + ":" + std::to_string(secs), 900, 270, 40);
    int fields_pressed = 0;
    int quanity2 = quanity;


    if (!Font.loadFromFile("fonts/pricedown.ttf"))
		return (-1);

    Tekst1.load();
    Tekst1.t.setFont(Font);
    Tekst2.load();
    Tekst2.t.setFont(Font);
    Tekst3.load();
    Tekst3.t.setFont(Font);

    srand(time(NULL));

    if (!music.openFromFile("sounds/NEVERGONNAGIVEYOUUP.wav"))
		return (-1);
    if(music_on)
        music.play();

    for(int q=0; q<12; q++) {
        Texture[q].loadFromFile("images/"+ std::to_string(q) +".png");
    }

    for(int q=0; q<mines; q++) {
        for(int w=0; w<mines; w++) {
        Sprite[q][w].setTexture(Texture[11]);
        Sprite[q][w].setScale(0.7,0.7);
        Sprite[q][w].setPosition(50+q*70,50+w*70);
        }
    }

    for(int q=0; q<mines; q++) {
        for(int w=0; w<mines; w++) {
            fields[q][w].pos_x = 50+q*70;
            fields[q][w].pos_y = 50+w*70;
            fields[q][w].scale = 100*0.7;
        }
    }


    while(quanity2) {
        rand_x = rand()%mines;
        rand_y = rand()%mines;
        if(!fields[rand_x][rand_y].is_mine) {
            fields[rand_x][rand_y].is_mine = true;
            fields[rand_x][rand_y].value = 9;
            quanity2--;
        }
    }
    quanity2 = quanity;

    for(int q=0; q<mines; q++) {
        for(int w=0; w<mines; w++) {
            if(fields[q][w].is_mine) {
                if (!(q-1<0 || w-1 <0 || fields[q-1][w-1].is_mine)) fields[q-1][w-1].value++;
                if (!(q<0 || w-1 <0 || fields[q][w-1].is_mine)) fields[q][w-1].value++;
                if (!(q+1>9 || w-1 <0 || fields[q+1][w-1].is_mine)) fields[q+1][w-1].value++;
                if (!(q-1<0 || w<0 || fields[q-1][w].is_mine)) fields[q-1][w].value++;
                if (!(q+1>9 || w<0 || fields[q+1][w].is_mine)) fields[q+1][w].value++;
                if (!(q-1<0 || w+1>9 || fields[q-1][w+1].is_mine)) fields[q-1][w+1].value++;
                if (!(q<0 || w+1>9 || fields[q][w+1].is_mine)) fields[q][w+1].value++;
                if (!(q+1>9 || w+1>9 || fields[q+1][w+1].is_mine)) fields[q+1][w+1].value++;
            }
        }
    }

    while (Running)
    {
        sf::Time Time = Clock.getElapsedTime();
        secs = Time.asSeconds();
        if(secs>59) {
            mins++;
            secs = 0;
            Clock.restart();
            if(mins>59) {
                mins = 0;
                hours++;
            }
        }



        sf::Vector2i pos = sf::Mouse::getPosition(App);
        int mouse_x = pos.x;
        int mouse_y = pos.y;

        while (App.pollEvent(Event))
		{

			if (Event.type == sf::Event::Closed)
				return (-1);
            if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left) {
                for(int q=0; q<mines; q++) {
                    for(int w=0; w<mines; w++) {
                        if(fields[q][w].is_pressed(mouse_x, mouse_y) && !fields[q][w].is_flag) {
                            if(!fields[q][w].is_clicked) {
                                fields_pressed++;
                                fields[q][w].is_clicked = true;
                            }
                            Sprite[q][w].setTexture(Texture[fields[q][w].value]);
                            if(fields[q][w].value==9) {
                                Sprite[0][0].setTexture(Texture[fields[0][0].value]);
                                for(int i=0; i<mines; i++) {
                                    for(int j=0; j<mines; j++) {
                                        Sprite[i][j].setTexture(Texture[fields[i][j].value]);
                                    }
                                }
                                Sleep(1000);
                                win = false;
                                return(4);
                            }

                        }
                    }
                }
            }

            if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Right) {
                for(int q=0; q<mines; q++)
                    for(int w=0; w<mines; w++)
                        if(fields[q][w].is_pressed(mouse_x, mouse_y) && !fields[q][w].is_clicked) {
                            if(!fields[q][w].is_flag) {
                                if(quanity2) {
                                    Sprite[q][w].setTexture(Texture[10]);
                                    fields[q][w].is_flag = true;
                                    quanity2--;
                                }
                            }
                            else {
                                Sprite[q][w].setTexture(Texture[11]);
                                fields[q][w].is_flag = false;
                                quanity2++;
                            }
                        }

            }

            if((fields_pressed + quanity ) == mines*mines) {
                win = true;
                return 4;
            }

		}



		Tekst2.t.setString(std::to_string(hours) + ":" + std::to_string(mins) + ":" + std::to_string(secs));
        Tekst3.t.setString("Liczba min: " + std::to_string(quanity2));

		App.clear(sf::Color(50,50,50));

        for(int q=0; q<mines; q++) {
            for(int w=0; w<mines; w++) {
                App.draw(Sprite[q][w]);
            }
        }
        App.draw(Tekst1.t);
        App.draw(Tekst2.t);
        App.draw(Tekst3.t);

        App.display();

    }

    return 0;
}
