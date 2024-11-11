#include "stdafx.h"
#include "ImguiManger.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "GUI.h"

#include "HierachyGUI.h"
#include "InspectorGUI.h"

bool ImguiManger::Init(sf::RenderWindow& window, bool loadDefaultFont)
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	bool isSuccess = ImGui::SFML::Init(window, loadDefaultFont);
	ImGui::NewFrame();

	ImGui::EndFrame();

	CreateUI();

	return isSuccess;
}

void ImguiManger::Release()
{
	ImGui::SFML::Shutdown();

	for (auto& gui : guiMap)
	{
		delete gui.second;
	}
	guiMap.clear();
}

void ImguiManger::CreateUI()
{
	HierachyGUI* hierachyGUI = new HierachyGUI("Hierachy");
	hierachyGUI->init();
	guiMap.insert({ hierachyGUI->GetName(), hierachyGUI });

	InspectorGUI* inspectorGUI = new InspectorGUI("Inspector");
	inspectorGUI->init();
	guiMap.insert({ inspectorGUI->GetName(), inspectorGUI });

	hierachyGUI->SetInspectorGUI(inspectorGUI);
}

void ImguiManger::ProcessEvent(const sf::Window& window, const sf::Event& event)
{
	ImGui::SFML::ProcessEvent(window, event);
}

void ImguiManger::Update(sf::RenderWindow& window, sf::Time dt)
{
	ImGui::SFML::Update(window, TimeManager::GetInstance().GetTime());

	//ImGui::Begin("Window title");

	for (const auto& pair : guiMap)
	{
		if (pair.second->IsActive())
		{
			pair.second->update();
		}
	}

	/*if (ImGui::CollapsingHeader("Help"))
	{
	}*/

	ImGui::ShowDemoWindow();
	//ImGui::End();
	ImGui::EndFrame();
}

void ImguiManger::Render(sf::RenderWindow& window)
{
	ImGui::SFML::Render(window);
}
