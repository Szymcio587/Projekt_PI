//załadowanie bibliotek i def. klasy z wirtualną funkcją Run, która jest dziedziczona przez wszystkie inne klasy
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App) = 0;
};
