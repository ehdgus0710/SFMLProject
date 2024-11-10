#include "stdafx.h"
#include "InspectorGUI.h"

#include "imgui.h"

InspectorGUI::InspectorGUI(const std::string& name)
	: GUI(name)
	, targetObject(nullptr)
{
}

InspectorGUI::~InspectorGUI()
{
}


void InspectorGUI::init()
{
}

void InspectorGUI::update()
{
	if (targetObject == nullptr)
		return;

	bool b = true;

	ImGui::Begin(GetName().c_str(), &b);

	if (targetObject  != nullptr && targetObject->GetDestory())
	{
		targetObject = nullptr;
	}

	auto name = GetName().c_str();
	sf::Vector2f position = targetObject->GetPosition();
	float pos[2] = { position.x, position.y };
	sf::Vector2f scale = targetObject->GetScale();
	float scaleArr[2] = { scale.x, scale.y };
	float rotation = targetObject->GetRotation();

	ImGui::Text("Position"); ImGui::SameLine(); 
	if (ImGui::InputFloat2("##Position", pos))
	{
		position.x = pos[0];
		position.y = pos[1];
		targetObject->SetPosition(position);
	}
	ImGui::Text("Scale   "); ImGui::SameLine(); 
	if (ImGui::InputFloat2("##Scale", scaleArr))
	{
		scale.x = scaleArr[0];
		scale.y = scaleArr[1];
		targetObject->SetScale(scale);
	}
	ImGui::Text("Rotation"); ImGui::SameLine(); 
	if (ImGui::InputFloat("##Rotation", &rotation))
	{
		targetObject->SetRotation(rotation);
	}


	ImGui::BeginChild(GetName().c_str(), {100.f,100.f});

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.8f));

	// ImGui::Button(COMPONENT_TYPE_STRING[(int)m_eComType]);

	ImGui::PopStyleColor(3);
	//ImGui::PopID();

	ImGui::EndChild();

	ImGui::End();
	//ImGui::Separator();
}

void InspectorGUI::SetObject(GameObject* object)
{ 
	targetObject = object;
}
