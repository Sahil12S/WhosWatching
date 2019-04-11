#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "../Game.h"
#include "../Game_Components/HUD.h"
#include "../Game_Components/Button.h"

namespace SSEngine
{
    class MainMenuState : public State
    {
    public:
        explicit MainMenuState( GameDataRef data );
        ~MainMenuState();

        void Init() override;
        void HandleInput(float dt) override;
        void Update( float dt ) override;
        void Draw() override;

    private:
        /* Variables */
        GameDataRef m_Data;

        std::map<std::string, int> m_KeyBinds;

        sf::RectangleShape m_Background;

        HUD* m_Hud;

        std::map<std::string, Button*> m_Buttons;

        /* Functions */
        // Initializers
        void InitKeyBinds();
        void InitTextures();
        void InitFonts();
        void InitSounds();
        void InitButtons();

        void InitVariables();

    };
}
#endif // MAIN_MENU_STATE_H