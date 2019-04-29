#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"
#include "State.h"
#include "MainMenuState.h"
#include "PauseMenu.h"
#include "../Game.h"
#include "../Game_Components/HUD.h"
#include "../Game_Components/Button.h"
#include "../Map/TileMap.h"

namespace SSEngine
{
class EditorState : public State
{
private:
    GameDataRef m_Data;

    sf::RectangleShape m_Background;
    HUD* m_Hud;
    PauseMenu* m_PauseMenu;
    TileMap* m_Map;

    std::map<std::string, int> m_KeyBinds;
    std::map<std::string, Button*> m_Buttons;

    bool m_Paused;

    // Initializers
    void InitKeyBinds();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitVariables();
    void InitComponents();
    void InitTexts();
    void InitPauseMenu();

public:
    EditorState( GameDataRef data );
    ~EditorState();

    void PauseState();
    void UnpauseState();

    void Init() override;
    void HandleInput( float dt ) override;
    void UpdateComponents( const float& dt );
    void UpdatePauseMenuButtons();
    void Update( float dt ) override;
    void Draw() override;
};
}

#endif