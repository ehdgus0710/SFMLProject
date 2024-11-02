#pragma once

class Animation;

class Animator : public Entity
{
protected:
	std::unordered_map<std::string, Animation*> animationMap;
	Animation*									currentAnimation;
	sf::Sprite									sprite;
	sf::IntRect									uvRect;
	bool										isPlaying;

public:
	Animation* GetAnimation(const std::string& animationName);

	void CreateAnimation(const std::string id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void CreateAnimation(const sf::Texture* texture, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);

	void ChangeAnimation(const std::string& animationName, bool isRepeat = false);
	void Render(sf::RenderWindow& renderWindow);
	void SetCurrentFrameRect(const sf::IntRect& rect);
	sf::Sprite& GetCurrentSprite() { return sprite; }

	//void Test1();
	//void Test2();

public:
	void Update(const float& deltaTime) override;
	void Start() override;
	bool Save() const override { return true; }
	bool Load() override { return true; }


public:
	Animator();	
	Animator(const Animator& other);
	~Animator();
};

