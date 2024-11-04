#include "stdafx.h"

#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(sf::Vector2f size)
	: rectangleSize(size)
	, rectanglePosition(size)
	, Collision(ColliderType::Rectangle)
	, rectanleRender(size)
{
	Init();
}

CollisionRectangle::~CollisionRectangle()
{
}

void CollisionRectangle::Init()
{
	rectanleRender.setFillColor(sf::Color::Transparent);
	rectanleRender.setOutlineColor(sf::Color::Green);
	rectanleRender.setOutlineThickness(1);
	rectanleRender.setOrigin(rectangleSize * 0.5f);
	SetSize(rectangleSize);
}

void CollisionRectangle::Update()
{
	Collision::Update();
}

void CollisionRectangle::Render(sf::RenderWindow& renderWindow)
{
	if (collisionCount > 0)
		rectanleRender.setOutlineColor(sf::Color::Red);
	else
		rectanleRender.setOutlineColor(sf::Color::Green);

	renderWindow.draw(rectanleRender);
}

void CollisionRectangle::Reset()
{
}

void CollisionRectangle::SetSize(sf::Vector2f size)
{
	rectangleSize = size;
	rectanglePosition.SetSize(size);
}

void CollisionRectangle::SetPosition(const sf::Vector2f& pos)
{
	rectanleRender.setPosition(pos);
	Collision::SetPosition(pos);
}
