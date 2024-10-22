#pragma once
class GameObject : public Entity
{
protected:
	sf::Vector2f position;
	sf::Vector2f rotation;
	sf::Vector2f scale;


	sf::Vector2f origin;
	Origins		originPreset;

	std::string name;
	bool active = true;
public:
	void Awake() override;
	void Start() override;

	virtual void Init();
	virtual void Release();
	virtual void Reset();

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	virtual void Render(sf::RenderWindow& renderWindow);

public:
	const bool IsActive() const { return active; }
	void SetActive(const bool active) { this->active = active; }
	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

public:
	bool Save() const override;
	bool Load() override;
public:
	GameObject(const std::string& name);
	virtual ~GameObject() {}
	GameObject(const GameObject& other);
	//GameObject& operator=(const GameObject&& other);
};

