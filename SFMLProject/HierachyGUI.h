#pragma once
#include "GUI.h"

#include "Scene.h"
class InspectorGUI;

class HierachyGUI : public GUI
{
protected:
	Scene*			currentScene;
	InspectorGUI*	currentObjectInspector;

public:
	virtual void Init();
	virtual void Update();
	void SetInspectorGUI(InspectorGUI* inspectorGUI) { currentObjectInspector = inspectorGUI; }

public:
	HierachyGUI(const std::string& name);
	virtual ~HierachyGUI();
};

