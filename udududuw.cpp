#include "hpp/screen_0.hpp"

int main()
{

    //tablica scen tzn. osobnych widoków(menu, opcje itd.)
	std::vector<cScreen*> Screens;
	int screen = 0;

	sf::RenderWindow App(sf::VideoMode(1200, 800, 32), "Minesweeper!!!1!1!!11!", sf::Style::Close);

	//załadowanie ich
	screen_0 s0;
	Screens.push_back(&s0);
	screen_1 s1;
	Screens.push_back(&s1);
    screen_2 s2;
	Screens.push_back(&s2);
    screen_3 s3;
	Screens.push_back(&s3);
    screen_4 s4;
	Screens.push_back(&s4);

	//pętla główna gry
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
		/*
            w zależności od tego, co zwróci metoda Run(App), ekran zmieni się na inny, pozostanie taki sam, lub też
            nastąpi wyjście z pętli, czyli zakończenie gry, jeśli zwrócona zostanie wartość ujemna
		*/
	}

	return EXIT_SUCCESS;
}
