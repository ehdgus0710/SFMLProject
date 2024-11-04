#pragma once

#include "Collision.h"

class Collider
{
private:
	static int		globalCount;

	sf::Vector2f	position;
	sf::Vector2f	offsetPosition;
	sf::Vector2f	colliderScale;
	sf::Vector2f	colliderRotation;

	Collision*		collision;
	ColliderLayer	colliderLayer;

	uint64_t		iD;
	int				collisionCount;
	bool			active;

public:
	Collision* GetCollision() const { return collision; }
	ColliderType GetColliderType();
	uint64_t GetID() const { return iD; }

	bool GetActive() const { return active; }
	void SetActive(bool active) { this->active = active; }

	bool GetDestory();

	void SetOffsetPosition(const sf::Vector2f& offset);
	void SetPosition(const sf::Vector2f& pos);
	void SetOrigin(const sf::Vector2f& origin);
	void SetOrigin(const Origins& origins);

	void SetScale(sf::Vector2f size);

	sf::Vector2f GetOffsetPosition() { return offsetPosition; }
	sf::Vector2f GetPosition();
	sf::Vector2f GetScale();

public:
	void Reset();

	void CreateCollision(ColliderType colliderType, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);

	virtual void Render(sf::RenderWindow& renderWindow);
	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);

public:
	Collider(ColliderType colliderType, ColliderLayer clliderLayer, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);
	~Collider();
};
