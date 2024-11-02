#include "stdafx.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"


Animation::Animation()
	: texture(nullptr)
	, totalFrameTime(0.f)
	, currentAnimationTime(0.f)
	, frameCount(0)
	, currentIndex(0)
	, isRepeat(false)
	, isPlaying(false)
	, isUnscale(false)
	, animator(nullptr)
{
}

Animation::Animation(const sf::Texture* texture, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
	: texture(texture)
	, totalFrameTime(0.f)
	, currentAnimationTime(0.f)
	, frameCount(frameCount)
	, currentIndex(0)
	, isRepeat(isRepeat)
	, isPlaying(false)
	, isUnscale(false)
	, animator(nullptr)

{
	frameInfoVector.clear();

	sf::Vector2u textureSize = texture->getSize();
	sf::Vector2u textureFrameCount = { textureSize.x / rectSize.x ,textureSize.y / rectSize.y };

	int totalCount = textureFrameCount.x * textureFrameCount.y;
	int count = 0;
	int topPos = 0;

	for (int i = 0; i < frameCount; ++i)
	{
		AnimationInfo frameInfo;

		frameInfo.uvRect.left = rectSize.x * count;
		frameInfo.uvRect.top = rectSize.y * topPos;
		frameInfo.uvRect.width = rectSize.x;
		frameInfo.uvRect.height = rectSize.y;

		frameInfo.duration = frameTime;
		frameInfo.rectSize = rectSize;

		totalFrameTime += frameTime;
		frameInfoVector.push_back(frameInfo);

		++count;
		if (count == textureFrameCount.x)
		{
			count = 0;
			++topPos;
		}
	}
}

Animation::Animation(const Animation& other)
	: animator(nullptr)
	, texture(other.texture)
	, frameCount(other.frameCount)
	, currentIndex(0)
	, totalFrameTime(other.totalFrameTime)
	, currentAnimationTime(0.f)
	, isUnscale(false)
	, isPlaying(false)
	, isRepeat(false)
{	
	int count = (int)other.frameInfoVector.size();
	for (int i = 0; i < count; ++i)
	{
		AnimationInfo info = other.frameInfoVector[i];
		frameInfoVector.push_back(info);
	}
}

Animation::~Animation()
{
}

void Animation::CreateAnimationInfo(const sf::Texture* texture, const sf::Vector2u& rectSize, int frameCount, float frameTime, bool isRepeat)
{
	sf::Vector2u textureSize = texture->getSize();
	sf::Vector2u textureFrameCount = { textureSize.x / rectSize.x ,textureSize.y / rectSize.y };
	int count = 0;
	int topPos = 0;

	for (int i = 0; i < frameCount; ++i)
	{
		AnimationInfo frameInfo;

		frameInfo.uvRect.left = rectSize.x * i;
		frameInfo.uvRect.top = 0;
		frameInfo.uvRect.width = rectSize.x;
		frameInfo.uvRect.height = rectSize.y;

		frameInfo.duration = frameTime;
		frameInfo.rectSize = rectSize;

		totalFrameTime += frameTime;
		frameInfoVector.push_back(frameInfo);

		++count;
		if (count == textureFrameCount.x)
		{
			count = 0;
			++topPos;
		}
	}
}


void Animation::Play(bool isRepeat)
{
	Reset();
	// animationStartEvnet;
	this->isRepeat = isRepeat;
	isPlaying = true;

	if (animator != nullptr)
		animator->SetCurrentFrameRect(frameInfoVector[currentIndex].uvRect);
}

void Animation::Stop()
{
	isPlaying = false;
}

void Animation::Reset()
{
	currentIndex = 0;
	currentAnimationTime = 0.f;
}

void Animation::Update(float deltaTime)
{
	if (!isPlaying)
		return;

	currentAnimationTime += deltaTime;

	if (currentAnimationTime >= frameInfoVector[currentIndex].duration)
	{
		currentAnimationTime -= frameInfoVector[currentIndex++].duration;

		if (currentIndex == frameCount)
		{
			if (isRepeat)
				currentIndex = 0;
			else
			{
				Stop();
				return;
			}

		}
		animator->SetCurrentFrameRect(frameInfoVector[currentIndex].uvRect);
	}
}

void Animation::AddAnimationInfo(const AnimationInfo& animationInfo, unsigned int index)
{
	if (frameCount <= index)
	{
		AddAnimationInfo(animationInfo);
	}
	else
	{
		auto iter = frameInfoVector.begin() + index;
		frameInfoVector.insert(iter, animationInfo);

		totalFrameTime += animationInfo.duration;
		++frameCount;
	}
}

void Animation::AddAnimationInfo(const AnimationInfo& animationInfo)
{
	frameInfoVector.push_back(animationInfo);

	totalFrameTime += animationInfo.duration;
	++frameCount;
}

void Animation::SetAnimationInfo(const AnimationInfo& animationInfo, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index] = animationInfo;
}

void Animation::SetRectSize(sf::Vector2u rectSize, unsigned int index)
{
	if (index >= frameCount)
		return;

	frameInfoVector[index].rectSize = rectSize;
}

void Animation::SetAnimationEvent(void* event, unsigned int index)
{
	if (index >= frameCount)
		return;

	// frameInfoVector[index].animationEvent = event;
}
