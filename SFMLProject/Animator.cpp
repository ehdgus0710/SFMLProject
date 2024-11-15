#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"
#include "rapidcsv.h"


Animator::Animator(GameObject* owner, sf::Sprite& sprite)
	: sprite(&sprite)
	, currentAnimation(nullptr)
	, isPlaying(false)
	, owner(owner)
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

void Animator::CreateAnimation(const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	CreateAnimation(&ResourcesManager<sf::Texture>::GetInstance().Get(id), id, animationName, rectSize, frameCount, frameTime, isRepeat);
}

void Animator::CreateAnimation(const sf::Texture* texture, const std::string& id, const std::string& animationName, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	if (animationMap.end() != animationMap.find(animationName))
		return;

	Animation* animation = new Animation(texture, id, animationName, rectSize, frameCount, frameTime, isRepeat);
	animationMap.insert({ animationName ,animation });
	animation->SetAnimator(this);

	if (currentAnimation == nullptr)
		StartAnimation(animation, isRepeat);
}

void Animator::AddAnimation(Animation* animation, const std::string& animationName)
{
	if (animationMap.find(animationName) != animationMap.end())
		return;

	animation->SetAnimator(this);
	animationMap.insert({ animationName, animation });

	if (currentAnimation == nullptr)
		StartAnimation(animation, animation->IsRepeat());
}

void Animator::ChangeAnimation(const std::string& animationName, bool isRepeat)
{
	auto animation = animationMap.find(animationName);
	if (animationMap.end() == animation)
		return;

	isPlaying = true;
	currentAnimation->SetRepeat(false);
	currentAnimation = animation->second;

	sprite->setTexture(*currentAnimation->GetTexture(), true);
	currentAnimation->Play(isRepeat);
}

void Animator::StartAnimation(Animation* animation, bool isRepeat)
{
	isPlaying = true;
	currentAnimation = animation;
	sprite->setTexture(*currentAnimation->GetTexture(), true);
	currentAnimation->Play(isRepeat);
}

void Animator::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(*sprite);
}

void Animator::SetCurrentFrameRect(const sf::IntRect& rect)
{
	uvRect = rect;
	// Utils::SetOrigin(*sprite, uvRect, owner->GetOrigins());
	sprite->setTextureRect(uvRect);
}

void Animator::SetCurrentFrameSize(const sf::Vector2u& size)
{
	//sprite->setOrigin((sf::Vector2f)size * 0.5f);
	Utils::SetOrigin(*sprite, uvRect, owner->GetOrigins());
}

void Animator::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	Utils::SetOrigin(*sprite, preset);
}

void Animator::SetOrigin(const sf::Vector2f& newOrigin)
{
	/*origins = Origins::Custom;
	originPosition = newOrigin;*/
	sprite->setOrigin(newOrigin);
}

void Animator::Test1()
{
	ChangeAnimation("PlayerMove");
}

void Animator::Test2()
{
	ChangeAnimation("PlayerDash");
}

sf::FloatRect Animator::GetLocalBounds() const
{
	return sprite->getLocalBounds();
}

sf::FloatRect Animator::GetGlobalBounds() const
{
	return  sprite->getGlobalBounds();
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
	// this->GetAnimation("PlayerDash")->functest = std::bind(&Animator::Test1, this);
	// this->GetAnimation("PlayerMove")->functest = std::bind(&Animator::Test2, this);

}

bool Animator::Save() const
{
	

	return false;
}

bool Animator::Load()
{
	return false;
}

bool Animator::SaveCsv(const std::string& filePath) const
{
	std::ofstream outFile(filePath);

	outFile << "ANIMATIONCSVPATH,ANIMAIONID" << std::endl;

	for (auto& animation : animationMap)
	{
		outFile << std::endl;
		auto resource = ResourcesManager<Animation>::GetInstance().GetResource(animation.first);
		outFile << resource.GetFilePath() + "," + resource.GetKey();
	}
	return true;
}

bool Animator::LoadCsv(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	std::string animationCsvPath;
	std::string animationId;
	for (int i = 2; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		animationCsvPath = row[0];
		animationId = row[1];

		ResourcesManager<Animation>::GetInstance().Load(animationId, animationCsvPath);
		Animation* animation = &ResourcesManager<Animation>::GetInstance().Get(animationId);
		AddAnimation(animation, animationId);
	}
	return true;
}
