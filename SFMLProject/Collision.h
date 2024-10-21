#pragma once

class Collision
{
protected:
	ColliderType colliderType;
	sf::Vector2f position;

	int collisionCount;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render(sf::RenderWindow renderWindow);

	void IsCollision() { ++collisionCount; }
	void EndCollision() { --collisionCount; }

	const ColliderType GetColliderType() { return colliderType; }
public:
	Collision(ColliderType colliderType);
	~Collision() {}

};

