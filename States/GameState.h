#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "../Game.h"
#include "../Entities/Player.h"
#include "../Map/TileMap.h"

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

        sf::Sprite m_BackgroundSprite;

        /* Functions */
        // Initializers
        void InitKeyBinds();
        void InitTextures();
        void InitFonts();
        void InitSounds();
        void InitComponents();

        void InitVariables();


    public:
        GameState( GameDataRef data );
        ~GameState();

        void Init() override;
        void HandleInput( float dt ) override;
        void Update( float dt ) override;
        void Draw() override;
    };
}
#endif // GAME_STATE_H