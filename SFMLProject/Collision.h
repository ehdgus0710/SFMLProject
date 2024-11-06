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
	void IsCollision() { ++collisionCount; }
	void EndCollision() { --collisionCount; }

	virtual void SetScale(const sf::Vector2f& scale);
	virtual sf::Vector2f GetScale() const = 0;

	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f GetPosition() { return position; }

	virtual void SetOrigin(const Origins& origins) = 0;
	virtual sf::Vector2f GetOrigin() { return originPosition; }

	const ColliderType GetColliderType() { return colliderType; }

public:
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Update();
	virtual void Render(sf::RenderWindow& renderWindow);

public:
	Collision(ColliderType colliderType);
	virtual ~Collision() {}

};

