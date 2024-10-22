#pragma once
class Utils
{
public:
	static sf::Vector2f SetOrigin(sf::Sprite& object, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& object, Origins preset);
};

