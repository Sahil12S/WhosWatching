#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "../Game.h"
#include "../Entities/Player.h"
#include "../Map/TileMap.h"
#include "PauseMenu.h"

namespace SSEngine
{
class GameState : public State
{
private:
    /* Variables */
    GameDataRef m_Data;

    std::map<std::string, int> m_KeyBinds;

    Player* m_Player;
    TileMap* m_Map;
    PauseMenu* m_PauseMenu;

    sf::Sprite m_BackgroundSprite;

    float m_KeyTime;
    float m_KeyTimeMax;
    bool m_Paused;

    /* Functions */
    // Initializers
    void InitKeyBinds();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitPauseMenu();
    void InitComponents();

    void InitVariables();


public:
    GameState( GameDataRef data );
    ~GameState();

    void PauseState();
    void UnpauseState();


    void Init() override;
    void HandleInput( float dt ) override;

    const bool GetKeyTime();
    
    void UpdatePauseMenuButtons();
    void UpdateKeyTime( const float& dt );
    void Update( float dt ) override;
    void Draw() override;
};
}
#endif // GAME_STATE_H