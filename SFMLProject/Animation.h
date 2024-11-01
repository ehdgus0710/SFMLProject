#pragma once

struct AnimationInfo
{
	float 
};

class Animation
{

public:
	std::vector<AnimationInfo>	frameInfoVector;
	int							frameCount;

public:
	Animation();
	virtual ~Animation();
};

