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

class EditorState : public State
{
private:
    GameDataRef m_Data;

    gui::HUD* m_Hud;
    PauseMenu* m_PauseMenu;
    TileMap* m_TileMap;

    std::map<std::string, int> m_KeyBinds;
    std::map<std::string, gui::Button*> m_Buttons;

    bool m_Paused;

    sf::RectangleShape m_SelectorRect;

    // Places a rectangle on tile sheet which decides which texture we are using.
    sf::IntRect m_textureRect;

    sf::Text m_CursorText;

    // Initializers
    void InitKeyBinds();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitVariables();
    void InitTexts();
    void InitPauseMenu();
    void InitTileMap();
    void InitComponents();

public:
    EditorState( GameDataRef data );
    ~EditorState();

    void PauseState();
    void UnpauseState();

    void Init() override;
    void HandleInput( float dt ) override;
    void UpdateComponents( const float& dt );
    void UpdateButtons();
    void UpdatePauseMenuButtons();
    void Update( float dt ) override;
    void Draw() override;
};

#endif