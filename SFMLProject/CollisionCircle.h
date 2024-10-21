#pragma once

#include "Collision.h"

class CollisionCircle : public Collision
{
private:
	float radian;
	sf::CircleShape collisionCircle;

public:
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);

	void SetRadian(float radian) { this->radian = radian; }
	float GetRadian() const { return radian; }

public:
	CollisionCircle(float radian);
	~CollisionCircle();
};

