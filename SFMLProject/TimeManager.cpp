#include "TimeManager.h"
#include "Core.h"

#include <time.h>

TimeManager::TimeManager()
	: deltaTime(0.f)
	, fixedTime(0.f)
	, frameTarget(144)
	, timeScale(1)
{
}


void TimeManager::Init()
{
	clock.restart();
}

inline void TimeManager::Update()
{
	deltaTime = sfTime.asSeconds() * timeScale;
}
