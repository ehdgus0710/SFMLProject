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

    for (int i = 0; i < size; ++i)
    {
        int objectCount = (int)objectVectors[i].size();
        for (int j = 0; j < objectCount; ++j)
        {
            const std::string& name = objectVectors[i][j]->GetName();
            if (name == "")
                continue;

            if (ImGui::Selectable(name.c_str(), selected == j))
            {
                selected = j;
                currentObjectInspector->SetObject(objectVectors[i][j]);
                currentObjectInspector->Activate();
                currentObjectInspector->update();
            }
            //if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
            //{
            //    selected = j;
            //    ImGui::Text("This a popup for \"%s\"!", name);
            //    if (ImGui::Button("Close"))
            //        ImGui::CloseCurrentPopup();
            //    ImGui::EndPopup();
            //}
            //ImGui::SetItemTooltip("Right-click to open popup");

        }
    }

    //for (auto& objectVector  : objectVectors)
    //{
    //    for (auto& object : objectVector)
    //    {
    //        if (ImGui::Selectable(object->GetName(), selected == n))
    //            selected = n;
    //        if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
    //        {
    //            selected = n;
    //            ImGui::Text("This a popup for \"%s\"!", names[n]);
    //            if (ImGui::Button("Close"))
    //                ImGui::CloseCurrentPopup();
    //            ImGui::EndPopup();
    //        }
    //        ImGui::SetItemTooltip("Right-click to open popup");
    //    }
    //}

    //const char* names[5] = { "Label1", "Label2", "Label3", "Label4", "Label5" };
    //for (int n = 0; n < 5; n++)
    //{
    //    if (ImGui::Selectable(names[n], selected == n))
    //        selected = n;
    //    if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
    //    {
    //        selected = n;
    //        ImGui::Text("This a popup for \"%s\"!", names[n]);
    //        if (ImGui::Button("Close"))
    //            ImGui::CloseCurrentPopup();
    //        ImGui::EndPopup();
    //    }
    //    ImGui::SetItemTooltip("Right-click to open popup");
    //}
	ImGui::End();
}

