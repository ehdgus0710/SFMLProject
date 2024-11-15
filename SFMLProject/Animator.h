#pragma once

class Animation;

class Animator : public Entity
{
protected:
	std::unordered_map<std::string, Animation*> animationMap;
	Animation*									currentAnimation;
	sf::Sprite*									sprite;
	sf::IntRect									uvRect;

	GameObject*									owner;
	bool										isPlaying;

protected:
	void StartAnimation(Animation* animation, bool isRepeat = false);

public:
	Animation* GetAnimation(const std::string& animationName);

	void CreateAnimation(const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void CreateAnimation(const sf::Texture* texture, const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void AddAnimation(Animation* animation, const std::string& animationName);

	void ChangeAnimation(const std::string& animationName, bool isRepeat = false);
	void Render(sf::RenderWindow& renderWindow);
	void SetCurrentFrameRect(const sf::IntRect& rect);
	void SetCurrentFrameSize(const sf::Vector2u& size);
	sf::Sprite& GetCurrentSprite() { return *sprite; }


	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);

	void Test1();
	void Test2();

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	void Update(const float& deltaTime) override;
	void Start() override;
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;


public:
	Animator(GameObject* owner, sf::Sprite& sprite);
	Animator(const Animator& other);
	~Animator();
};

