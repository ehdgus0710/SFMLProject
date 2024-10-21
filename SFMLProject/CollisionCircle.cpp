#include "stdafx.h"
#include "CollisionCircle.h"


CollisionCircle::CollisionCircle(float radian)
	: radian(radian)
	, Collision(ColliderType::Circle)
	, collisionCircle(radian)
{
	collisionCircle.setOutlineColor(sf::Color::Green);
}

CollisionCircle::~CollisionCircle()
{
}

void CollisionCircle::Update()
{
	Collision::Update();
}

void CollisionCircle::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(collisionCircle);
}
