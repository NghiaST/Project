#include <SFML/Graphics.hpp>
#include "notepad.hpp"
#include "notepad2.hpp"
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    int number = 10;
    print(number);
    cout << check(number * 3) << '\n';
}