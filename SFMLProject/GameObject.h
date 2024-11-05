#pragma once
class GameObject : public Entity
{
protected:
	sf::Vector2f	position;
	float			rotation;
	sf::Vector2f	scale;
	sf::Vector2f	origin;

	Collider*		collider;
	Origins			originPreset;

	std::string		name;
	bool			active = true;

public:
	const bool IsActive() const { return active; }
	void SetActive(const bool active) { this->active = active; }
	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	virtual void SetScale(const sf::Vector2f& scale);
	virtual sf::Vector2f GetScale() const { return scale; }

	virtual void SetRotation(float angle) { rotation = angle; }
	virtual float GetRotation() { return rotation; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos);

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}


	virtual bool CreateCollider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);
	Collider* GetCollider() { return collider; }
public:
	void Awake() override;
	void Start() override;

	virtual void Release();

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	virtual void Render(sf::RenderWindow& renderWindow);

	virtual void OnCollisionEnter(Collider* target) {}
	virtual void OnCollisionStay(Collider* target) {}
	virtual void OnCollisionEnd(Collider* target) {}

public:
	bool Save() const override;
	bool Load() override;
public:
	GameObject(const std::string& name);
	virtual ~GameObject();
	GameObject(const GameObject& other);
	//GameObject& operator=(const GameObject&& other);
};

