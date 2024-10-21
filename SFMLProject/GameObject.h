#pragma once
class GameObject : public Entity
{
protected:
	sf::Vector2f position;
	sf::Vector2f rotation;
	sf::Vector2f scale;

public:
	void Awake() override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	virtual void Render(const sf::RenderWindow& renderWindow);

public:
	bool Save() const override;
	bool Load() override;
public:
	GameObject() {}
	virtual ~GameObject() {}
	GameObject(const GameObject& other) {}
	GameObject& operator=(const GameObject&& other) {}
};

