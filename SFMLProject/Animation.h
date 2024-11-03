#pragma once

class Animator;

struct AnimationInfo
{
	sf::IntRect		uvRect;
	sf::Vector2u	rectSize;
	float			duration;
};

class Animation
{
protected:
	Animator*					animator;
	std::vector<AnimationInfo>	frameInfoVector;
	const sf::Texture*			texture;

	unsigned int				frameCount;
	unsigned int				currentIndex;
	float						totalFrameTime;
	float						currentAnimationTime;

	bool						isUnscale;
	bool						isPlaying;
	bool						isRepeat;

public:

	typedef std::function<void()> Event;
	std::function<void()> functest;
	//void(Animator::* onFunc)();
	//std::function<void(Animator&)> func;

public:
	void Play(bool isRepeat = false);
	void Stop();
	void Reset();

	void Update(float deltaTime);

public:
	void AddAnimationInfo(const AnimationInfo& animationInfo, unsigned int index);
	void AddAnimationInfo(const AnimationInfo& animationInfo);

	void CreateAnimationInfo(const sf::Texture* texture, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat = false);
	void SetAnimationInfo(const AnimationInfo& animationInfo, unsigned int index);
	void SetRectSize(sf::Vector2u rectSize, unsigned int index);
	void SetRepeat(bool repeat) { isRepeat = repeat; }
	void SetUnScaleUpdate(bool unscale) { isUnscale = unscale; }

	void SetAnimationEvent(void* event, unsigned int index);
	void SetAnimator(Animator* animator) { this->animator = animator; }
	const sf::Texture* GetTexture() const { return texture; }

public:
	Animation();
	Animation(const sf::Texture* texture, const sf::Vector2u& rectSize, int frameCount ,float frameTime, bool isRepeat = false);
	Animation(const Animation& other);
	virtual ~Animation();
};

