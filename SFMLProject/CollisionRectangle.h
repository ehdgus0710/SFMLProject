#pragma once

#include "Collision.h"

struct Rectangle
{
	float leftPosition;
	float rightPosition;
	float topPosition;
	float bottomPosition;
	Rectangle()
		: leftPosition(0)
		, rightPosition(0)
		, topPosition(0)
		, bottomPosition(0)
	{

	}
	Rectangle(sf::Vector2f size)
	{
		SetSize(size);
	}

	void SetSize(sf::Vector2f size)
	{
		leftPosition = size.x * 0.5f * -1.f;
		topPosition = size.y * 0.5f * -1.f;
		rightPosition = leftPosition  * -1.f;
		bottomPosition = topPosition * -1.f;
	}
};

class CollisionRectangle : public Collision
{
private:
	sf::Vector2f rectangleSize;
	sf::RectangleShape rectanleRender;
	Rectangle rectanglePosition;

public:
	void Init() override;

	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);

	void SetSize(sf::Vector2f size);
	sf::Vector2f GetScale() const override { return rectanleRender.getSize(); }
	const sf::FloatRect& GetRect() { return rectanleRender.getGlobalBounds(); }
	void SetPosition(const sf::Vector2f& pos) override;

	sf::Vector2f GetLeftTopPosition() { return { position.x + rectanglePosition.leftPosition , position.y + rectanglePosition.topPosition }; }
	sf::Vector2f GetRightBottomPosition() { return { position.x + rectanglePosition.rightPosition , position.y + rectanglePosition.bottomPosition }; }
	sf::Vector2f GetRightTopPosition() { return { position.x + rectanglePosition.rightPosition , position.y + rectanglePosition.topPosition }; }
	sf::Vector2f GetLeftBottomPosition() { return { position.x + rectanglePosition.leftPosition , position.y + rectanglePosition.topPosition }; }

	float GetLeftPosition() { return position.x + rectanglePosition.leftPosition; }
	float GetRightPosition() { return position.x + rectanglePosition.rightPosition; }
	float GetTopPosition() { return position.y + rectanglePosition.topPosition; }
	float GetBottomPosition() { return position.y + rectanglePosition.bottomPosition; }

public:
	CollisionRectangle(sf::Vector2f size = sf::Vector2f::one);
	~CollisionRectangle();

};

