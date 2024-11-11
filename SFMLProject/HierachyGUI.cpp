#include "stdafx.h"
#include "HierachyGUI.h"

#include "ImguiManger.h"
#include "imgui.h"
#include "InspectorGUI.h"

HierachyGUI::HierachyGUI(const std::string& name)
	: GUI(name)
    , currentScene(nullptr)
    , currentObjectInspector(nullptr)
{
}

HierachyGUI::~HierachyGUI()
{
}
void HierachyGUI::init()
{
}

void HierachyGUI::update()
{
	bool b = true;
    static int selected = -1;

	ImGui::Begin(GetName().c_str(), &b);

    currentScene = SceneManager::GetInstance().GetCurrentScene();
    const std::vector<std::vector<GameObject*>>& objectVectors = currentScene->GetObjectVectors();
    int size = (int)objectVectors.size();

    int currentPos = 0;

    for (int i = 0; i < size; ++i)
    {
        int objectCount = (int)objectVectors[i].size();
        for (int j = 0; j < objectCount; ++j)
        {
            const std::string& name = std::to_string(objectVectors[i][j]->GetID())+ ". " + objectVectors[i][j]->GetName();
            if (ImGui::Selectable(name.c_str(), selected == currentPos))
            {
                selected = currentPos;
                currentObjectInspector->SetObject(objectVectors[i][j]);
                currentObjectInspector->Activate();
                currentObjectInspector->update();
            }
            ++currentPos;
        }
    }

	ImGui::End();
}

