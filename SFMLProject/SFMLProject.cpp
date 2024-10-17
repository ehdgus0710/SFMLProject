#include "Core.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2f test;
    test.Normalized(); 
    sf::Texture texBee;
    if (!texBee.loadFromFile("graphics/bee.png"))
    {

    }

    sf::Sprite bee;
    bee.setTexture(texBee);
    test = (texBee.getSize() / 2.f);

    //test = sf::Vector2f::Lerp(left, right, 0.5f);

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