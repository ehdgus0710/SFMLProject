#pragma once
class Rigidbody : public Entity
{
protected:
	GameObject* owner;

	sf::Vector2f    accel;
	sf::Vector2f	velocity;
	sf::Vector2f	force;

	float	mass;
	float	dropSpeed;
	float	maxDropSpeed;
	bool    friction;
	bool	isGround;
public:
	void SetVelocity(const sf::Vector2f& velocity);
	sf::Vector2f GetCurrentVelocity() const { return velocity; }

	void AddForce(const sf::Vector2f& force);
	sf::Vector2f GetCurrentForce() const { return force; }

	float GetMass() const { return mass; }
	void SetMass(float mass) { this->mass = mass; }

	void SetGround(bool isGround);
	bool IsGround() const { return isGround; }

	void SetMaxDropSpeed(float speed) { maxDropSpeed = speed; }
	float GetMaxDropSpeed() { return maxDropSpeed; }

	void SetOwner(GameObject* owner) { this->owner = owner; }
	GameObject* GetOwner() { return owner; }

public:
	void FixedUpdate(const float& fixedDeltaTime) override;

	void Awake() override;
	void Start() override;

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	Rigidbody(GameObject* owner);
	virtual ~Rigidbody();
};

