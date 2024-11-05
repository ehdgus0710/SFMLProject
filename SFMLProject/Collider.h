#pragma once

class Collision;

class Collider
{
private:
	static int		globalCount;

	sf::Vector2f	position;
	sf::Vector2f	offsetPosition;
	sf::Vector2f	colliderScale;
	sf::Vector2f	colliderRotation;

	GameObject* owner;
	ColliderLayer	colliderLayer;

	Collision*		collision;

	std::vector<Collider*> collisionTagetVector;

	uint64_t		iD;
	int				collisionCount;
	bool			active;
	bool			isDestory;

public:
	Collision* GetCollision() const { return collision; }
	ColliderType GetColliderType();
	ColliderLayer GetColliderLayer() { return colliderLayer; }
	uint64_t GetID() const { return iD; }

	bool GetActive() const { return active; }
	void SetActive(bool active) { this->active = active; }

	void OnDestory();
	bool IsDestory();

	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f GetPosition();

	void SetOffsetPosition(const sf::Vector2f& offset);
	sf::Vector2f GetOffsetPosition() { return offsetPosition; }

	void SetScale(sf::Vector2f size);
	sf::Vector2f GetScale();

	void SetOrigin(const sf::Vector2f& origin);
	void SetOrigin(const Origins& origins);

	void SetOwner(GameObject* owner) { this->owner = owner; }
	GameObject* GetOwner() { return owner; }

	const std::vector<Collider*>& GetCollisionTarget() { return collisionTagetVector; }

public:
	void Reset();
	void CreateCollision(ColliderType colliderType, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);

	virtual void Render(sf::RenderWindow& renderWindow);
	void OnCollisionEnter(Collider* target);
	void OnCollisionStay(Collider* target);
	void OnCollisionEnd(Collider* target);

public:
	Collider(ColliderType colliderType, ColliderLayer clliderLayer, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);
	Collider(const Collider& other);
	~Collider();
};
