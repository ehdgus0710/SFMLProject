#pragma once

#include "Collision.h"
struct Rectangle
{
	float leftPosition;
	float rightPosition;
	float topPosition;
	float bottomPosition;

	Rectangle(float left, float rgiht, float top, float bottom)
		: leftPosition(left)
		, rightPosition(rgiht)
		, topPosition(top)
		, bottomPosition(bottom)
	{

	}

	Rectangle(sf::Vector2f position, sf::Vector2f size)
		: leftPosition(position.x - size.x * 0.5f)
		, rightPosition(position.x + size.x * 0.5f)
		, topPosition(position.y - size.y * 0.5f)
		, bottomPosition(position.y + size.y * 0.5f)
	{

	}
};

class CollisionRectangle : public Collision
{
private:
	sf::RectangleShape rectanleRender;

public:
	void SetScale(const sf::Vector2f& scale) override;
	sf::Vector2f GetScale() const override { return rectanleRender.getSize(); }

	// Rectangle GetRect() {return }
	sf::FloatRect GetRect() { return sf::FloatRect{ position,rectanleRender.getSize() }; }
	void SetPosition(const sf::Vector2f& pos) override;

	sf::Vector2f GetLeftTopPosition() { return { GetLeftPosition(),GetTopPosition() }; }
	sf::Vector2f GetRightBottomPosition() { return { GetRightPosition(),GetBottomPosition() }; }
	sf::Vector2f GetRightTopPosition() { return { GetRightPosition(),GetTopPosition() }; }
	sf::Vector2f GetLeftBottomPosition() { return { GetLeftPosition(),GetBottomPosition() }; }

	float GetLeftPosition() { return position.x - rectanleRender.getSize().x * 0.5; }
	float GetRightPosition() { return position.x + rectanleRender.getSize().x * 0.5; }
	float GetTopPosition() { return  position.y - rectanleRender.getSize().y * 0.5; }
	float GetBottomPosition() { return position.y + rectanleRender.getSize().y * 0.5; }

	void SetOrigin(const Origins& origins) override;
public:
	void Init() override;
	void Reset() override;
	void Update() override;
	void Render(sf::RenderWindow& renderWindow) override;

public:
	CollisionRectangle(sf::Vector2f size = sf::Vector2f::one);
	~CollisionRectangle();

};

