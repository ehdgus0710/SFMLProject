#include "InputManager.h"
#include "WindowManager.h"

inline void InputManager::Clear()
{
	keyboardInputMap.clear();
	mouseInputMap.clear();
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
			iter->second = KeyInput::KeyUp == iter->second ? KeyInput::KeyDown : KeyInput::KeyPressed;
		}
		else
			keyboardInputMap.insert({ ev.key.code , KeyInput::KeyDown });
	}
	break;
	case sf::Event::KeyReleased:
	{
		keyboardInputMap[ev.key.code] = KeyInput::KeyUp;
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
			iter->second = KeyInput::KeyUp == iter->second ? KeyInput::KeyDown : KeyInput::KeyPressed;
		}
		else
			mouseInputMap.insert({ ev.mouseButton.button , KeyInput::KeyDown });
	}
	break;
	case sf::Event::MouseButtonReleased:
		mouseInputMap[ev.mouseButton.button] = KeyInput::KeyUp;
		break;
	}
}

inline bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return  keyboardInputMap[key] == KeyInput::KeyDown;
}

inline bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return keyboardInputMap.find(key) != keyboardInputMap.end();
}

inline bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return keyboardInputMap[key] == KeyInput::KeyUp;
}

inline const sf::Vector2i InputManager::GetMousePosition() const
{
	return mousePosition;
}
