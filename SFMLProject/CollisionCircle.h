#pragma once

#include "Collision.h"

class CollisionCircle : public Collision
{
private:
	float radian;
	sf::CircleShape collisionCircle;

public:
	void Init();
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRadian(float radian) { this->radian = radian; }
	float GetRadian() const { return radian; }

	sf::Vector2f GetScale() const override { return sf::Vector2f::one * radian; };

public:
	CollisionCircle(float radian);
	~CollisionCircle();
};

