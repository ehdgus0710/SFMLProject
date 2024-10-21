#pragma once

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

