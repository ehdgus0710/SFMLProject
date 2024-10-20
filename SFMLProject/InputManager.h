#pragma once

#include "Core.h"

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
private:
	std::unordered_map<sf::Keyboard::Key, KeyState> keyboardInputMap;
	std::unordered_map<sf::Mouse::Button, KeyState> mouseInputMap;
	sf::Vector2i mousePosition;

public:
	void init();

	void UpdateEvent(const sf::Event& ev);
	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);
	void Clear();

	const sf::Vector2i GetMousePosition() const;

protected:
	InputManager() = default;
	~InputManager() override {}
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};

