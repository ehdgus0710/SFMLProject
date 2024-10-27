#include "stdafx.h"

inline void InputManager::Clear()
{
	keyboardInputMap.clear();
	mouseInputMap.clear();
}

bool InputManager::BindKey(const sf::Keyboard::Key& key)
{
	auto iter = keyboardInputMap.find(key);

	if (iter != keyboardInputMap.end())
		return false;

	keyboardInputMap.insert({ key , KeyState::KeyNone });
	return true;
}

bool InputManager::BindMouseButton(const sf::Mouse::Button& mouseButton)
{
	auto iter = mouseInputMap.find(mouseButton);

	if (iter != mouseInputMap.end())
		return false;

	mouseInputMap.insert({ mouseButton , KeyState::KeyNone });
	return true;
}

void InputManager::UpDownCheck()
{
	int size = (int)keyUpDownStateVector.size();
	for (int i = 0; i < size; ++i)
	{
		if(keyboardInputMap[keyUpDownStateVector[i]] == KeyState::KeyDown)
			keyboardInputMap[keyUpDownStateVector[i]] = KeyState::KeyPressed;
		else
			keyboardInputMap[keyUpDownStateVector[i]] = KeyState::KeyNone;
	}

	size = (int)mouseUpDownStateVector.size();
	for (int i = 0; i < size; ++i)
	{
		if (mouseInputMap[mouseUpDownStateVector[i]] == KeyState::KeyDown)
			mouseInputMap[mouseUpDownStateVector[i]] = KeyState::KeyPressed;
		else
			mouseInputMap[mouseUpDownStateVector[i]] = KeyState::KeyNone;
	}

	keyUpDownStateVector.clear();
	mouseUpDownStateVector.clear();
}

void InputManager::Init()
{
	BindKey(sf::Keyboard::Up);
	BindKey(sf::Keyboard::Down);
	BindKey(sf::Keyboard::Right);
	BindKey(sf::Keyboard::Left);
	BindKey(sf::Keyboard::Space);
	BindKey(sf::Keyboard::Z);
	BindKey(sf::Keyboard::F11);
	BindKey(sf::Keyboard::F1);
}

void InputManager::UpdateEvent(const sf::Event* ev)
{
	switch (ev->type)
	{
	case sf::Event::KeyPressed:
	{
		if (GetKey(ev->key.code))
		{
			keyboardInputMap[ev->key.code] = KeyState::KeyDown;
		}
	}
	break;
	case sf::Event::KeyReleased:
	{
		if (GetKey(ev->key.code))
		{
			keyboardInputMap[ev->key.code] = KeyState::KeyUp;
		}
	}
	break;
	case sf::Event::MouseButtonPressed:
	{
		if ((GetKey(ev->mouseButton.button)))
		{
			mouseInputMap[ev->mouseButton.button] = KeyState::KeyDown;
		}
	}
	break;
	case sf::Event::MouseButtonReleased:
	{
		if ((GetKey(ev->mouseButton.button)))
		{
			mouseInputMap[ev->mouseButton.button] = KeyState::KeyUp;
		}
	}
		break;
	case sf::Event::MouseMoved:
		mousePosition = sf::Mouse::getPosition(*WindowManager::GetInstance().GetRenderWindow());
		break;
	}
}

bool InputManager::GetKey(const sf::Keyboard::Key& key)
{
	return keyboardInputMap.find(key) != keyboardInputMap.end();
}

bool InputManager::GetKeyDown(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return  keyboardInputMap[key] == KeyState::KeyDown;
}

bool InputManager::GetKeyPressed(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return  keyboardInputMap[key] == KeyState::KeyPressed;
}

bool InputManager::GetKeyUp(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return keyboardInputMap[key] == KeyState::KeyUp;
}

bool InputManager::GetKey(const sf::Mouse::Button& button)
{
	return mouseInputMap.find(button) != mouseInputMap.end();
}

bool InputManager::GetKeyDown(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyDown;
}

bool InputManager::GetKeyPressed(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyPressed;
}

bool InputManager::GetKeyUp(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyUp;
}

const sf::Vector2i InputManager::GetMousePosition() const
{
	return mousePosition;
}
