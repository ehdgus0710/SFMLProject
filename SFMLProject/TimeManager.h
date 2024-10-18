#pragma once

#include "Singleton.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class TimeManager : public Singleton<TimeManager>
{
	friend Singleton<TimeManager>;
public:
	void Init();
	void Update();

	const float DeletaTime() const { return deltaTime; }
	const float FixedDeletaTime() const { return fixedTime; }
	const float GetElapsedTime() const 
	{
		return clock.getElapsedTime().asSeconds();
	}
	

private:
	sf::Clock		clock;
	sf::Time		sfTime;

	float			timeScale;
	float			deltaTime;
	float			fixedTime;
	unsigned int	frameTarget;

protected:
	TimeManager();
	~TimeManager() override {}
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
};

