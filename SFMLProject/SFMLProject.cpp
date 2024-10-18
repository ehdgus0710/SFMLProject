#include "Core.h"

#include "InputManager.h"
#include "ResourcesManager.h"
#include "TimeManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture texBee;
    if (!texBee.loadFromFile("graphics/bee.png"))
    {

    }
    
    //TimeManager::
    //ResourcesManager<sf::Texture>::GetInstance().

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

    return 0;
}