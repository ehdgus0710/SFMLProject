#pragma once

#include <SFML/Graphics.hpp>

class Framework
{
private:
	sf::RenderWindow*	renderWindow;
	sf::Event			event;
public:
	void init();
	void Update();
public:
	Framework();
	~Framework();
};

