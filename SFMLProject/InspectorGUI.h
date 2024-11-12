#pragma once
#include "GUI.h"
#include "GameObject.h"

class ComponentGUI;

struct OriginEnumDesc
{
	Origins origin;
	std::string originID;
};

class InspectorGUI : public GUI
{
protected:
	GameObject*					targetObject;
	std::vector<ComponentGUI*>	componetGUIvector;

private:
	void TransformInfo();

public:
	virtual void Init();
	virtual void Update();
	void SetObject(GameObject* object);

public:
	InspectorGUI(const std::string& name);
	virtual ~InspectorGUI();
};

