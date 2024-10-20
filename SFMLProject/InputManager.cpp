#include "InputManager.h"
#include "WindowManager.h"

inline void InputManager::Clear()
{
	keyboardInputMap.clear();
	mouseInputMap.clear();
}

void InputManager::init()
{

}

inline void InputManager::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	{
		auto iter = keyboardInputMap.find(ev.key.code);
		if (iter != keyboardInputMap.end())
		{
			iter->second = KeyState::KeyUp == iter->second ? KeyState::KeyDown : KeyState::KeyPressed;
		}
		else
			keyboardInputMap.insert({ ev.key.code , KeyState::KeyDown });
	}
	break;
	case sf::Event::KeyReleased:
	{
		keyboardInputMap[ev.key.code] = KeyState::KeyUp;
	}

	break;
	case sf::Event::MouseMoved:
		 mousePosition = sf::Mouse::getPosition(*WindowManager::GetInstance().GetRenderWindow());
		break;
	case sf::Event::MouseButtonPressed:
	{
		auto iter = mouseInputMap.find(ev.mouseButton.button);
		if (iter != mouseInputMap.end())
		{
			iter->second = KeyState::KeyUp == iter->second ? KeyState::KeyDown : KeyState::KeyPressed;
		}
		else
			mouseInputMap.insert({ ev.mouseButton.button , KeyState::KeyDown });
	}
	break;
	case sf::Event::MouseButtonReleased:
		mouseInputMap[ev.mouseButton.button] = KeyState::KeyUp;
		break;
	}
}

inline bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return  keyboardInputMap[key] == KeyState::KeyDown;
}

inline bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return keyboardInputMap.find(key) != keyboardInputMap.end();
}

inline bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return keyboardInputMap[key] == KeyState::KeyUp;
}

inline const sf::Vector2i InputManager::GetMousePosition() const
{
	return mousePosition;
}
