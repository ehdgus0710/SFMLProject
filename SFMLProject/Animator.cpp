#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"


Animator::Animator()
	: currentAnimation(nullptr)
	, isPlaying(false)
{
}

Animator::Animator(const Animator& other)
	: currentAnimation(nullptr)
	, uvRect(other.uvRect)
	, isPlaying(false)
{
	animationMap.clear();
	for (auto& animation : other.animationMap)
	{
		Animation* copyAnimation = new Animation(*animation.second);
		copyAnimation->SetAnimator(this);
		animationMap.insert({ animation.first, copyAnimation });
	}
}

Animator::~Animator()
{
	for (auto& animation : animationMap)
	{
		delete animation.second;
	}

	animationMap.clear();
}

Animation* Animator::GetAnimation(const std::string& animationName)
{
	auto animation = animationMap.find(animationName);
	
	if (animationMap.end() == animation)
		return nullptr;

	return animation->second;
}

void Animator::CreateAnimation(const std::string id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	CreateAnimation(&ResourcesManager<sf::Texture>::GetInstance().Get(id), animationName, rectSize, frameCount, frameTime, isRepeat);
}

void Animator::CreateAnimation(const sf::Texture* texture, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	if (animationMap.end() != animationMap.find(animationName))
		return;

	Animation* animation = new Animation(texture, rectSize, frameCount, frameTime, isRepeat);
	animationMap.insert({ animationName ,animation });
	animation->SetAnimator(this);
}

void Animator::ChangeAnimation(const std::string& animationName, bool isRepeat)
{
	auto animation = animationMap.find(animationName);
	if (animationMap.end() == animation)
		return;

	isPlaying = true;
	currentAnimation = animation->second;


	sprite.setTexture(*currentAnimation->GetTexture());
	currentAnimation->Play(isRepeat);
}

void Animator::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
}

void Animator::SetCurrentFrameRect(const sf::IntRect& rect)
{
	uvRect = rect;
	sprite.setTextureRect(uvRect);
}

void Animator::Test1()
{
	ChangeAnimation("PlayerMove");
}

void Animator::Test2()
{
	ChangeAnimation("PlayerDash");
}

void Animator::Update(const float& deltaTime)
{
	if(isPlaying)
		currentAnimation->Update(deltaTime);
}

void Animator::Start()
{
	//this->GetAnimation("PlayerDash")->func = std::move(std::bind(&Animator::Test1, this));
	//this->GetAnimation("PlayerMove")->func = std::move(std::bind(&Animator::Test2, this)); // = &Animator::Test2;
	this->GetAnimation("PlayerDash")->functest = std::bind(&Animator::Test1, this);
	this->GetAnimation("PlayerMove")->functest = std::bind(&Animator::Test2, this);
}
