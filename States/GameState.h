#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "../Game.h"
#include "../Entities/Player.h"
#include "../Map/TileMap.h"
#include "../Items/Callout.h"

class GameState : public State
{
private:
    /* Variables */
    GameDataRef m_Data;

    sf::View m_View;
    // We will load whole texture at one go
    sf::RenderTexture m_RenderTexture;
    sf::Sprite m_RenderSprite;

    std::map<std::string, int> m_KeyBinds;

    Player* m_Player;
    TileMap* m_TileMap;
    PauseMenu* m_PauseMenu;
    GameOverMenu* m_GOMenu;
    Callout* m_Callout;

    sf::Sprite m_BackgroundSprite;

    sf::Text m_CursorText;

    bool m_Paused;
    bool m_GameOver;
    bool isCallout;
    bool question;
    bool answer;

    int idx;

    std::map< std::string, gui::HUD* > hud;
    std::vector< std::pair<std::string, bool> > questionVec;

    std::string calloutMessage;
    std::list< std::string > startMessages;

    int maxScore;

    /* Functions */
    void fix_newlines( std::string& s );
    
    // Initializers
    void InitView();
    void InitVariables();
    void InitTextures();
    void InitFonts();
    void InitSounds();

    void InitKeyBinds();
    void InitPauseMenu();
    void InitGameOverMenu();
    void InitComponents();
    void InitTileMap();
    void InitPlayers();
    void InitCallout();

    void InitQuestions();



public:
    GameState( GameDataRef data );
    ~GameState();

    void PauseState();
    void UnpauseState();


    void Init() override;
    
    void UpdateView( const float& dt );
    void HandleInput( float dt ) override;

    void UpdateTileMap( const float& dt );
    void UpdatePauseMenuButtons();
    void UpdateGameOverMenuButtons();
    void UpdateCalloutButtons( const float& dt );
    void UpdateGui();

    void Update( float dt ) override;
    void Draw() override;
};
#endif // GAME_STATE_H