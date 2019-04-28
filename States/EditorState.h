#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"
#include "State.h"
#include "MainMenuState.h"
#include "../Game.h"
#include "../Game_Components/HUD.h"
#include "../Game_Components/Button.h"

namespace SSEngine
{
class EditorState : public State
{
private:
    GameDataRef m_Data;

    sf::RectangleShape m_Background;
    HUD* m_Hud;
    std::map<std::string, Button*> m_Buttons;

    // Initializers
    void InitKeyBinds();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitComponents();
    void InitVariables();
    void InitTexts();
public:
    EditorState( GameDataRef data );
    ~EditorState();

    void Init() override;

    void HandleInput( float dt ) override;
    void UpdateComponents( const float& dt );
    void Update( float dt ) override;
    void Draw() override;
};
}

#endif