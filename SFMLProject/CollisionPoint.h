#pragma once

#include "Collision.h"

class CollisionPoint : public Collision
{
private:
	sf::VertexArray vertexPoint;

public:
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);
	void SetPosition(const sf::Vector2f& pos) override;
	sf::Vector2f GetScale() const override { return sf::Vector2f::one; };

public:
	CollisionPoint();
	~CollisionPoint();
};

