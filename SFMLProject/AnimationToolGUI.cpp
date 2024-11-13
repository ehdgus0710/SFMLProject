#include "stdafx.h"
#include "AnimationToolGUI.h"
#include "imgui.h"

#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"

int AnimationToolGUI::frameID = 0;

AnimationToolGUI::AnimationToolGUI()
	: GUI("AnimationTool")
	, accTime(0.f)
	, isPlay(false)
	, isRepeat(false)
    , texture(nullptr)
    , isButton(false)
    , isAtlasTextrue(false)

{
}

AnimationToolGUI::~AnimationToolGUI()
{
}


void AnimationToolGUI::Init()
{
}

void AnimationToolGUI::Update()
{
    bool b = true;

    ImGui::Begin(GetName().c_str(), &b);


    if (ImGui::Button("TexLoad", { 100,30 })) 
        TextureLoad();
    ImGui::SameLine(); 
    if (ImGui::Button("AnimLoad", { 100,30 })) 
        AnimationLoad();

    static int item_current_idx = 0; // Here we store our selection data as an index.
    static ImGuiComboFlags flags = 0;
    static int iAnimIndexSize = 0;

    auto map = ResourcesManager<sf::Texture>::GetInstance().GetResourcesMap();

    //auto iter = map.begin();
    std::vector<std::string> keyVector;

    for (auto iter : map)
    {
        keyVector.push_back(iter.second->GetKey());
    }


    if (ImGui::BeginCombo("##Texture", keyVector[item_current_idx].c_str(), flags))
    {
        for (int n = 0; n < keyVector.size(); ++n)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(keyVector[n].c_str(), is_selected))
            {
                item_current_idx = n;
                texture = &ResourcesManager<sf::Texture>::GetInstance().Get(keyVector[n]);
                sprite.setTexture(*texture);
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    // �ؽ���	
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
    sf::Vector2u resolution = {};

    ImTextureID tex_id = 0;
    if (nullptr != texture)
    {
        tex_id = (ImTextureID)texture->getNativeHandle();		//�ؽ��� ���� Ȯ��
        resolution = texture->getSize();
    }

    if (texture)
        ImGui::Image(tex_id, ImVec2(resolution), uv_min, uv_max, tint_col, border_col);


    int index = frameID;
    sf::Vector2f leftTop = {};
    sf::Vector2f frameSize = {};

    ImGui::Text("FramSize"); ImGui::SameLine();
    if (ImGui::InputInt("##FramSize", &iAnimIndexSize))
    {
        if (animInfoVector.size() < iAnimIndexSize)
        {
            for (size_t i = animInfoVector.size(); i < iAnimIndexSize; ++i)
            {
                AnimationInfo info = {};
                if (i > 0)
                    info = animInfoVector[i - 1];

                info.duration = 0.01f;
                animInfoVector.push_back(info);
            }
        }
        else if (animInfoVector.size() > iAnimIndexSize)
        {
            for (size_t i = animInfoVector.size(); i > iAnimIndexSize; --i)
            {
                if (animInfoVector.size() - 1 == frameID)
                    --frameID;
                animInfoVector.pop_back();
            }
        }
    }

    if (0 < animInfoVector.size())
    {
        int maxCount = (int)animInfoVector.size() - 1;
        ImGui::Text("FrameIndex");;
        if (ImGui::InputInt("##FrameIndex", &index))
        {
            if(index <= maxCount&& index >= 0)
                frameID = index;
        }

        if (texture != nullptr)
        {
            if (ImGui::Button("ChangeButton", { 100, 20 }))
                isButton = !isButton;
            if (ImGui::Button("IsAtlasTexture", { 100, 20 }))
                isAtlasTextrue = !isAtlasTextrue;

            if (isAtlasTextrue)
                AtlasTextrue();
            else
                DefaultTextrue();

            ImGui::Text("Duration");
            ImGui::DragFloat("##DragDuration", &animInfoVector[frameID].duration, 0.05f, 0.01f, 5.f);
            ImGui::SliderFloat("##SliderDuration", &animInfoVector[frameID].duration, 0, 3.f);
        }

        std::string animationName;
        static char cName[100];
        ImGui::Text("Animation Name");
        ImGui::InputText("##Animation Name", cName, 100);     ImGui::SameLine();
        if (ImGui::Button("SetName", {100,30}))
        {
            animationName = cName;
        }

        sprite.setTextureRect(animInfoVector[frameID].uvRect);

        if (nullptr != texture) 
            ImGui::ImageButton(keyVector[item_current_idx].c_str(), sprite, { (float)animInfoVector[frameID].rectSize.x, (float)animInfoVector[frameID].rectSize.y });

        if (ImGui::Button("Play", { 100,30 }))
        {
            frameID = 0;
            isPlay = true;
        }
        ImGui::SameLine(); 
        if (ImGui::Button("repeat", { 100,30 }))
            isRepeat = !isRepeat;

        if (ImGui::Button("Animation Save", { 100,30 }))
        {
            AnimationSave(animationName);
        }

        if (isPlay) 
            AnimationPlay(frameID);
    }

    ImGui::End();
}

void AnimationToolGUI::TextureLoad()
{
}

void AnimationToolGUI::AnimationSave(const std::string& animationName)
{
    // csv ���̺� �ǰ� ����

}

void AnimationToolGUI::AnimationLoad()
{
    // csv �ε� �ϰ� ����

}

void AnimationToolGUI::Listinit()
{
}

void AnimationToolGUI::AnimationPlay(int& iFrmID)
{
    accTime += TimeManager::GetInstance().GetDeletaTime();
    if (accTime >= animInfoVector[iFrmID].duration)
    {
        accTime -= animInfoVector[iFrmID++].duration;

        if (iFrmID == animInfoVector.size())
        {
            if (isRepeat)
                iFrmID = 0;
            else
            {
                --iFrmID;
                isPlay = false;
            }
        }
    }

}

void AnimationToolGUI::ChangeToolVersion()
{
}

void AnimationToolGUI::AtlasTextrue()
{
    ImGui::Text("RectSize");

    int rectSizeArr[2] = { (int)atlasRectSize.x, (int)atlasRectSize.y };

    if (ImGui::DragInt2("##DragRectSize", rectSizeArr, 0.3f, 0, 5000))
    {
        atlasRectSize = { (unsigned int)rectSizeArr[0],(unsigned int)rectSizeArr[1] };
    }

    if (ImGui::SliderInt2("##SlideRectSize", rectSizeArr, 0, 1000))
    {
        atlasRectSize = { (unsigned int)rectSizeArr[0],(unsigned int)rectSizeArr[1] };
    }

    if (ImGui::Button("SetDefalutRectSize", { 200, 20 }) && atlasRectSize.x != 0 && atlasRectSize.y != 0)
    {
        int size = (int)animInfoVector.size();
        for (int i = 0; i < size; ++i)
        {
            animInfoVector[i].rectSize = atlasRectSize;
            animInfoVector[i].uvRect.left = i * atlasRectSize.x;
            animInfoVector[i].uvRect.top = i * atlasRectSize.y;

            animInfoVector[i].uvRect.width = atlasRectSize.x;
            animInfoVector[i].uvRect.height = atlasRectSize.y;
        }
    }

    ImGui::Text("LeftPosition");
    ImGui::DragInt("##DragLeftPosition", &animInfoVector[frameID].uvRect.left, 0.5f, 0, texture->getSize().x);
    ImGui::SliderInt("##SliderLeftPosition", &animInfoVector[frameID].uvRect.left, 0, texture->getSize().x);

    ImGui::Text("TopPosition");
    ImGui::DragInt("##DragTopPosition", &animInfoVector[frameID].uvRect.top, 0.5f, 0, texture->getSize().y);
    ImGui::SliderInt("##SliderTopPosition", &animInfoVector[frameID].uvRect.top, 0, texture->getSize().y);

    ImGui::Text("WidthRange");
    ImGui::DragInt("##DragWidthRange", &animInfoVector[frameID].uvRect.width, 0.5f, 0, texture->getSize().x);
    ImGui::SliderInt("##SliderWidthRange", &animInfoVector[frameID].uvRect.width, 0, texture->getSize().x);

    ImGui::Text("HeightRange");
    ImGui::DragInt("##DragHeightRange", &animInfoVector[frameID].uvRect.height, 0.5f, 0, texture->getSize().y);
    ImGui::SliderInt("##SliderHeightRange", &animInfoVector[frameID].uvRect.height, 0, texture->getSize().y);
}

void AnimationToolGUI::DefaultTextrue()
{
    if (isButton)
    {
        static int calculateArray[2] = {};
        ImGui::InputInt("SizeXCount", &calculateArray[0]);
        ImGui::InputInt("SizeYCount", &calculateArray[1]);
        if (ImGui::Button("GetCalculateRectSize", { 200, 20 }) && calculateArray[0] != 0 && calculateArray[1] != 0)
        {
            rectSize = texture->getSize();
            rectSize.x /= calculateArray[0];
            rectSize.y /= calculateArray[1];
        }

        ImGui::SameLine();
        if (ImGui::Button("SetDefalutRectSize", { 200, 20 }) && rectSize.x != 0 && rectSize.y != 0)
        {
            int size = (int)animInfoVector.size();
            int posLeft = 0;
            int posTop = 0;
            int posWidth = rectSize.x;
            int posHegiht = rectSize.y;
            int test = texture->getSize().x;
            for (int i = 0; i < size; ++i)
            {
                animInfoVector[i].rectSize = rectSize;
                animInfoVector[i].uvRect.left = posLeft = (i % (texture->getSize().x / posWidth)) * posWidth;
                animInfoVector[i].uvRect.top = posTop = i / (test / posWidth) * rectSize.y;

                animInfoVector[i].uvRect.width = posWidth;
                animInfoVector[i].uvRect.height = posHegiht;
            }
        }
    }

    ImGui::Text("RectSize");

    int rectSizeArr[2] = { (int)animInfoVector[frameID].rectSize.x, (int)animInfoVector[frameID].rectSize.y };

    if (ImGui::DragInt2("##DragRectSize", rectSizeArr, 0.3f, 0, 5000))
    {
        animInfoVector[frameID].rectSize = { (unsigned int)rectSizeArr[0],(unsigned int)rectSizeArr[1] };
        animInfoVector[frameID].rectSize;
    }

    if (ImGui::SliderInt2("##SlideRectSize", rectSizeArr, 0, 1000))
    {
        animInfoVector[frameID].rectSize = { (unsigned int)rectSizeArr[0],(unsigned int)rectSizeArr[1] };
        animInfoVector[frameID].rectSize;
    }

    if (!isButton)
    {
        ImGui::Text("LeftPosition");
        ImGui::DragInt("##DragLeftPosition", &animInfoVector[frameID].uvRect.left, 0.5f, 0, texture->getSize().x);
        ImGui::SliderInt("##SliderLeftPosition", &animInfoVector[frameID].uvRect.left, 0, texture->getSize().x);

        ImGui::Text("TopPosition");
        ImGui::DragInt("##DragTopPosition", &animInfoVector[frameID].uvRect.top, 0.5f, 0, texture->getSize().y);
        ImGui::SliderInt("##SliderTopPosition", &animInfoVector[frameID].uvRect.top, 0, texture->getSize().y);

        ImGui::Text("WidthRange");
        ImGui::DragInt("##DragWidthRange", &animInfoVector[frameID].uvRect.width, 0.5f, 0, texture->getSize().x);
        ImGui::SliderInt("##SliderWidthRange", &animInfoVector[frameID].uvRect.width, 0, texture->getSize().x);

        ImGui::Text("HeightRange");
        ImGui::DragInt("##DragHeightRange", &animInfoVector[frameID].uvRect.height, 0.5f, 0, texture->getSize().y);
        ImGui::SliderInt("##SliderHeightRange", &animInfoVector[frameID].uvRect.height, 0, texture->getSize().y);

    }
}