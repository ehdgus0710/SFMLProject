#pragma once

#include "GUI.h"
#include "Animation.h"

class AnimationToolGUI : public GUI
{

private:
    sf::Sprite                  sprite;
    sf::Texture*                texture;
    std::vector<std::string>    textureVector;
    std::vector<AnimationInfo>  animInfoVector;
    std::string                 textureID;
    sf::Vector2u                rectSize;

    float                       accTime;
    bool                        isPlay;
    bool                        isRepeat;
    bool                        isButton;

public:
    void Init() override;
    void Update() override;

    void TextureLoad();
    void AnimationSave(const std::string& animationName);
    void AnimationLoad();
private:
    void Listinit();
    void AnimationPlay(int& iFrmID);
    void ChangeToolVersion();

public:
    AnimationToolGUI();
    ~AnimationToolGUI();
};

