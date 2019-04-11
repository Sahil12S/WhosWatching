#ifndef GAME_SETTINGS_STATE_H
#define GAME_SETTINGS_STATE_H

#include "../Game.h"
#include "State.h"
#include "../Game_Components/HUD.h"
#include "../Game_Components/Button.h"

namespace SSEngine
{
    class GameSettingsState : public State
    {
    private:
        /* Variables */
        GameDataRef m_Data;

        HUD* m_Hud;

        std::map<std::string, int> m_KeyBinds;

        sf::RectangleShape m_Background;

        std::map<std::string, Button*> m_Buttons;

        /* Functions */
        // Initializers
        void InitKeyBinds();
        void InitTextures();
        void InitFonts();
        void InitSounds();
        void InitButtons();

        void InitVariables();


    public:
        GameSettingsState( GameDataRef data );
        ~GameSettingsState();

        // Initializes the state
        void Init() override;

        void HandleInput( float dt ) override;
        void Update( float dt ) override;
        void Draw() override;
    };
}

#endif // GAME_SETTINGS_STATE_H