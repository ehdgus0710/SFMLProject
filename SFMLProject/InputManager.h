#pragma once

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
private:
	std::unordered_map<sf::Keyboard::Key, KeyState> keyboardInputMap;
	std::unordered_map<sf::Mouse::Button, KeyState> mouseInputMap;
	//std::unordered_map<, KeyState> mouseInputMap;

	std::vector<sf::Keyboard::Key>					keyUpDownStateVector;
	std::vector<sf::Mouse::Button>					mouseUpDownStateVector;
	sf::Vector2i									mousePosition;


public:
	bool BindKey(const sf::Keyboard::Key& key);
	bool BindMouseButton(const sf::Mouse::Button& mouseButton);

	void UpDownCheck();

	const sf::Vector2i GetMousePosition() const;

public:
	void Init();
	void UpdateEvent(const sf::Event* ev);

	bool GetKey(const sf::Keyboard::Key& key);
	bool GetKeyDown(const sf::Keyboard::Key& key);
	bool GetKeyPressed(const sf::Keyboard::Key& key);
	bool GetKeyUp(const sf::Keyboard::Key& key);

	bool GetKey(const sf::Mouse::Button& button);
	bool GetKeyDown(const sf::Mouse::Button& button);
	bool GetKeyPressed(const sf::Mouse::Button& button);
	bool GetKeyUp(const sf::Mouse::Button& button);

	void Clear();

protected:
	InputManager() = default;
	~InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};

