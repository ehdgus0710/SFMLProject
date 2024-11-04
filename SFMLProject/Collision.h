#pragma once

class Collision
{
protected:
	ColliderType colliderType;

	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f originPosition;
	

	int collisionCount;
public:
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Update();
	virtual void Render(sf::RenderWindow& renderWindow);

	void IsCollision() { ++collisionCount; }
	void EndCollision() { --collisionCount; }

	virtual void SetScale(const sf::Vector2f& scale);

	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f GetPosition() { return position; }

	virtual sf::Vector2f GetScale() const = 0;

	const ColliderType GetColliderType() { return colliderType; }
public:
	Collision(ColliderType colliderType);
	~Collision() {}

};

