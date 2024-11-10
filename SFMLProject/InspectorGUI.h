#pragma once
#include "GUI.h"
#include "GameObject.h"

class InspectorGUI : public GUI
{
protected:
	GameObject* targetObject;

public:
	virtual void init();
	virtual void update();
	void SetObject(GameObject* object);

public:
	InspectorGUI(const std::string& name);
	virtual ~InspectorGUI();
};

