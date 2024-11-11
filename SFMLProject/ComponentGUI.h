#pragma once

enum class ComponentGUIType
{
	Animator,
	Collider,
	TileMap,

	End
};

class ComponentGUI
{
protected:
	GameObject*			target;
	ComponentGUIType	type;

public:
	virtual void update() = 0;
	virtual void SetObject(GameObject* object) = 0;

public:
	ComponentGUI(ComponentGUIType type);
	~ComponentGUI();
};

