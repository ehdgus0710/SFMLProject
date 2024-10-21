#pragma once

#include "Collision.h"

struct Rectangle
{
	sf::Vector2f leftTopPosition;
	sf::Vector2f rightBottomPosition;

	Rectangle(sf::Vector2f size)
	{
		leftTopPosition.x = size.x / 2.f * -1.f;
		leftTopPosition.y = size.y / 2.f * -1.f; 
		rightBottomPosition.x = leftTopPosition.x * -1.f;
		rightBottomPosition.y = leftTopPosition.y * -1.f;
	}
};

class CollisionRectangle : public Collision
{
private:
	sf::Vector2f rectangleSize;
	sf::RectangleShape rectanleRender;
	Rectangle rectanglePosition;

public:
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);

	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize() const { return rectangleSize; }

	sf::Vector2f GetLeftTopPosition() { return position + rectanglePosition.leftTopPosition; }
	sf::Vector2f GetRightBottomPosition() { return position + rectanglePosition.rightBottomPosition; }
	sf::Vector2f GetRightTopPosition() { return position + sf::Vector2f(rectanglePosition.rightBottomPosition.x, rectanglePosition.leftTopPosition.y); }
	sf::Vector2f GetLeftBottomPosition() { return position + sf::Vector2f(rectanglePosition.leftTopPosition.x, rectanglePosition.rightBottomPosition.y); }

public:
	CollisionRectangle(sf::Vector2f size = sf::Vector2f::one);
	~CollisionRectangle();

};

