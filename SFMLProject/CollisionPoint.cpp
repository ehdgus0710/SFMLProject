#include "stdafx.h"
#include "CollisionPoint.h"


CollisionPoint::CollisionPoint()
	: Collision(ColliderType::Point)
{
}

CollisionPoint::~CollisionPoint()
{
}

void CollisionPoint::SetOrigin(const Origins& origins)
{
}

void CollisionPoint::Init()
{
}

void CollisionPoint::Reset()
{
}

void CollisionPoint::Update()
{
}

void CollisionPoint::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(vertexPoint);
}

void CollisionPoint::SetPosition(const sf::Vector2f& pos)
{
	vertexPoint[0].position = pos;
}