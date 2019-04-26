#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "../Game.h"
#include "../Game_Components/Button.h"
#include "../Game_Components/HUD.h"

// TODO: Remove Paused State and create on-screen pause
namespace SSEngine
{
    class PauseState : public  State
    {
    public:
        PauseState( GameDataRef data );
        ~PauseState();

        void Init() override ;

        void HandleInput(float dt) override ;

        void Update( float dt ) override;

        void Draw() override ;

    private:
        /* Variables */
        GameDataRef m_Data;

        HUD* m_Hud;

        std::map<std::string, int> m_KeyBinds;

        std::map<std::string, Button*> m_Buttons;

        sf::RectangleShape m_Background;

        /* Functions */
        // Initializers
        void InitKeyBinds();
        void InitTextures();
        void InitFonts();
        void InitSounds();
        void InitComponents();

        void InitVariables();

        // Handle title animation
        sf::Clock clock;
        bool movedLeft;
    };
}

#endif // PAUSE_STATE_H