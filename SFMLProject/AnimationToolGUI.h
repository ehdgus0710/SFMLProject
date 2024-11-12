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
    float                       accTime;
    bool                        isPlay;
    bool                        isRepeat;

public:
    void Init() override;
    void Update() override;

    void TextureLoad();
    void AnimationSave(std::string animationName);
    void AnimationLoad();
private:
    void Listinit();
    void AnimationPlay(int& iFrmID);
    void ChangeToolVersion();

public:
    AnimationToolGUI();
    ~AnimationToolGUI();
};

