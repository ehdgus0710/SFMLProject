#pragma once

#include "Collision.h"

class Collider
{
private:
	static int globalCount;
	sf::Vector2f offsetPosition;
	sf::Vector2f colliderScale;
	sf::Vector2f position;
	Collision* collision;

	uint64_t	iD;
	int			collisionCount;
	bool		active;

public:
	Collision* GetCollision() const { return collision; }
	ColliderType GetColliderType();
	uint64_t GetID() const { return iD; }

	bool GetActive() const { return active; }
	void SetActive(bool active) { this->active = active; }

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	sf::Vector2f GetScale() { return colliderScale; }

public:
	void CreateCollision(ColliderType colliderType, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);

	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);

public:
	Collider();
	~Collider();
};
