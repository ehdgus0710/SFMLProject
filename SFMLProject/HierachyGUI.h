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
	virtual void init();
	virtual void update();
	void SetInspectorGUI(InspectorGUI* inspectorGUI) { currentObjectInspector = inspectorGUI; }

public:
	HierachyGUI(const std::string& name);
	virtual ~HierachyGUI();
};

