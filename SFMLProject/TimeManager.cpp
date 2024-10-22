#include "stdafx.h"
#include "Core.h"

TimeManager::TimeManager()
	: deltaTime(0.f)
	, realDeltatime(0.f)
	, fixedTime(0.f)
	, frameTarget(144)
	, time(0.f)
	, realTime(0.f)
	, timeScale(1)
{
}


void TimeManager::Init()
{
	clock.restart();
}

void TimeManager::Update()
{
	sfTime = clock.restart();
	realDeltatime = deltaTime = sfTime.asSeconds();
	deltaTime *= timeScale;
	realDeltatime += realDeltatime;
	time += deltaTime;
}
